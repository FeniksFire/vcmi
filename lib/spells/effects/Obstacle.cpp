/*
 * Obstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "Obstacle.h"

#include "Registry.h"
#include "../ISpellMechanics.h"

#include "../../NetPacks.h"
#include "../../battle/IBattleState.h"
#include "../../battle/CBattleInfoCallback.h"
#include "../../serializer/JsonSerializeFormat.h"

static const std::string EFFECT_NAME = "core:obstacle";

namespace spells
{
namespace effects
{

VCMI_REGISTER_SPELL_EFFECT(Obstacle, EFFECT_NAME);

Obstacle::Obstacle()
	: LocationEffect(),
	hidden(false),
	passable(false),
	trigger(false),
	trap(false),
	removeOnTrigger(false),
	patchCount(1),
	turnsRemaining(-1)
{
}

Obstacle::~Obstacle() = default;

void Obstacle::adjustAffectedHexes(std::set<BattleHex> & hexes, const Mechanics * m, const Target & spellTarget) const
{
	EffectTarget effectTarget = transformTarget(m, spellTarget, spellTarget);

	auto options = area.at(m->casterSide);

	for(auto & destination : effectTarget)
	{
		options.moveAreaToField(destination.hexValue);
		
		for(auto & hex : options.getFields())
		{
			if(hex.isValid())
				hexes.insert(hex);
		}
	}
}

bool Obstacle::applicable(Problem & problem, const Mechanics * m) const
{
	return LocationEffect::applicable(problem, m);
}

bool Obstacle::applicable(Problem & problem, const Mechanics * m, const EffectTarget & target) const
{
	if(!m->isMassive())
	{
		const bool requiresClearTiles = m->requiresClearTiles();
		auto options = area.at(m->casterSide);

		if(target.empty())
			return noRoomToPlace(problem, m);

		for(const auto & destination : target)
		{
			options.moveAreaToField(destination.hexValue);
			
			for(auto & hex : options.getFields())
			{
				if(!isHexAvailable(m->cb, hex, requiresClearTiles))
					return noRoomToPlace(problem, m);
			}
		}
	}

	return LocationEffect::applicable(problem, m, target);
}

EffectTarget Obstacle::transformTarget(const Mechanics * m, const Target & aimPoint, const Target & spellTarget) const
{
	auto options = area.at(m->casterSide);

	EffectTarget ret;

	if(!m->isMassive())
	{
		for(auto & spellDestination : spellTarget)
		{
			options.moveAreaToField(spellDestination.hexValue);
			
			for(auto & hex : options.getFields())
			{
				ret.emplace_back(hex);
			}
		}
	}

	return ret;
}

void Obstacle::apply(BattleStateProxy * battleState, RNG & rng, const Mechanics * m, const EffectTarget & target) const
{
	if(m->isMassive())
	{
		std::vector<BattleHex> availableTiles;
		for(int i = 0; i < GameConstants::BFIELD_SIZE; i++)
		{
			BattleHex hex = i;
			if(isHexAvailable(m->cb, hex, true))
				availableTiles.push_back(hex);
		}
		RandomGeneratorUtil::randomShuffle(availableTiles, rng);

		const int patchesToPut = std::min<int>(patchCount, availableTiles.size());

		EffectTarget randomTarget;
		randomTarget.reserve(patchesToPut);
		for(int i = 0; i < patchesToPut; i++)
			randomTarget.emplace_back(availableTiles.at(i));

		placeObstacles(battleState, m, randomTarget);
	}
	else
	{
		placeObstacles(battleState, m, target);
	}
}

void Obstacle::serializeJsonEffect(JsonSerializeFormat & handler)
{
	ObstacleJson json1(handler.getCurrent()["attacker"]);
	ObstacleJson json2(handler.getCurrent()["defender"]);
	
	handler.serializeBool("hidden", hidden);
	handler.serializeBool("passable", passable);
	handler.serializeBool("trigger", trigger);
	handler.serializeBool("trap", trap);
    handler.serializeBool("removeOnTrigger", removeOnTrigger);

	handler.serializeInt("patchCount", patchCount);
	handler.serializeInt("turnsRemaining", turnsRemaining, -1);
	
	area.at(BattleSide::ATTACKER) = json1.getArea();
	area.at(BattleSide::DEFENDER) = json2.getArea();
	info.at(BattleSide::ATTACKER) = json1.getGraphicsInfo();
	info.at(BattleSide::DEFENDER) = json2.getGraphicsInfo();
}

bool Obstacle::isHexAvailable(const CBattleInfoCallback * cb, const BattleHex & hex, const bool mustBeClear)
{
	if(!hex.isAvailable())
		return false;

	if(!mustBeClear)
		return true;

	if(cb->battleGetUnitByPos(hex, true))
		return false;

	auto obst = cb->battleGetAllObstaclesOnPos(hex, false);

	for(auto & i : obst)
		if(i->getType() != ObstacleType::MOAT)
			return false;

	if(cb->battleGetSiegeLevel() != 0)
	{
		EWallPart::EWallPart part = cb->battleHexToWallPart(hex);

		if(part == EWallPart::INVALID || part == EWallPart::INDESTRUCTIBLE_PART_OF_GATE)
			return true;//no fortification here
		else if(static_cast<int>(part) < 0)
			return false;//indestructible part (cant be checked by battleGetWallState)
		else if(part == EWallPart::BOTTOM_TOWER || part == EWallPart::UPPER_TOWER)
			return false;//destructible, but should not be available
		else if(cb->battleGetWallState(part) != EWallState::DESTROYED && cb->battleGetWallState(part) != EWallState::NONE)
			return false;
	}

	return true;
}

bool Obstacle::noRoomToPlace(Problem & problem, const Mechanics * m)
{
	MetaString text;
	text.addTxt(MetaString::GENERAL_TXT, 181);//No room to place %s here
	text.addReplacement(m->getSpellName());
	problem.add(std::move(text));
	return false;
}

void Obstacle::placeObstacles(BattleStateProxy * battleState, const Mechanics * m, const EffectTarget & target) const
{
	auto options = area.at(m->casterSide);
	auto graphicsinfo = info.at(m->casterSide);

	BattleObstaclesChanged pack;

	auto all = m->cb->battleGetAllObstacles(BattlePerspective::ALL_KNOWING);

	for(const Destination & destination : target)
	{
		SpellCreatedObstacle obstacle;
		
		options.moveAreaToField(destination.hexValue);
		obstacle.setArea(options);
		
		obstacle.ID = SpellID(m->getSpellIndex());

		obstacle.turnsRemaining = turnsRemaining;
		obstacle.casterSpellPower = m->getEffectPower();
		obstacle.spellLevel = m->getEffectLevel();//todo: level of indirect effect should be also configurable
		obstacle.casterSide = m->casterSide;

		obstacle.hidden = hidden;
		obstacle.passable = passable;
		obstacle.trigger = trigger;
		obstacle.trap = trap;
		obstacle.removeOnTrigger = removeOnTrigger;
		
		obstacle.setGraphicsInfo(graphicsinfo);
		
		pack.changes.emplace_back();
		obstacle.toInfo(pack.changes.back());
	}

	if(!pack.changes.empty())
		battleState->apply(&pack);
}


}
}
