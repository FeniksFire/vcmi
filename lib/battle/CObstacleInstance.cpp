/*
 * CObstacleInstance.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "CObstacleInstance.h"
#include "../CTownHandler.h"
#include "../VCMI_Lib.h"
#include "../spells/CSpellHandler.h"
#include "filesystem/ResourceID.h"
#include "battle/obstacle/ObstacleInfo.h"

CObstacleInstance::CObstacleInstance() : config(JsonNode(ResourceID("config/obstacles.json"))["obstacles"])
{
	obstacleType = ObstacleType::USUAL;
	uniqueID = -1;
	ID = -1;
}

CObstacleInstance::~CObstacleInstance()
{

}

const ObstacleInfo CObstacleInstance::getInfo() const
{
	if(obstacleType == ObstacleType::ABSOLUTE_OBSTACLE)
		return  ObstacleInfo(JsonNode(ResourceID("config/obstacles.json"))["absoluteObstacles"].Vector().at(ID));;
	return ObstacleInfo(config.Vector().at(ID));
}

std::vector<BattleHex> CObstacleInstance::getBlockedTiles() const
{
	if(blocksTiles())
		return getAffectedTiles();
	return std::vector<BattleHex>();
}

std::vector<BattleHex> CObstacleInstance::getStoppingTile() const
{
	if(stopsMovement())
		return getAffectedTiles();
	return std::vector<BattleHex>();
}

std::vector<BattleHex> CObstacleInstance::getAffectedTiles() const
{
		return area.getFields();
}

bool CObstacleInstance::visibleForSide(ui8 side, bool hasNativeStack) const
{
	return true;
}

bool CObstacleInstance::stopsMovement() const
{
	return obstacleType == ObstacleType::QUICKSAND || obstacleType == ObstacleType::MOAT;
}

bool CObstacleInstance::blocksTiles() const
{
	return obstacleType == ObstacleType::USUAL || obstacleType == ObstacleType::ABSOLUTE_OBSTACLE || obstacleType == ObstacleType::FORCE_FIELD;
}

SpellCreatedObstacle::SpellCreatedObstacle()
{
	casterSide = -1;
	spellLevel = -1;
	casterSpellPower = -1;
	turnsRemaining = -1;
	visibleForAnotherSide = -1;
}

bool SpellCreatedObstacle::visibleForSide(ui8 side, bool hasNativeStack) const
{
	switch(obstacleType)
	{
	case ObstacleType::FIRE_WALL:
	case ObstacleType::FORCE_FIELD:
		return true;
	case ObstacleType::QUICKSAND:
	case ObstacleType::LAND_MINE:
		//we hide mines and not discovered quicksands
		//quicksands are visible to the caster or if owned unit stepped into that particular patch
		//additionally if side has a native unit, mines/quicksands will be visible
		return casterSide == side || visibleForAnotherSide || hasNativeStack;
	default:
		assert(0);
		return false;
	}
}

std::vector<BattleHex> SpellCreatedObstacle::getAffectedTiles() const
{
	switch(obstacleType)
	{
	case ObstacleType::QUICKSAND:
	case ObstacleType::LAND_MINE:
	case ObstacleType::FIRE_WALL:
		return std::vector<BattleHex>(1, area.position);
	case ObstacleType::FORCE_FIELD:
		return SpellID(SpellID::FORCE_FIELD).toSpell()->rangeInHexes(area.position, spellLevel, casterSide);
	default:
		assert(0);
		return std::vector<BattleHex>();
	}
}

void SpellCreatedObstacle::battleTurnPassed()
{
	if(turnsRemaining > 0)
		turnsRemaining--;
}

std::vector<BattleHex> MoatObstacle::getAffectedTiles() const
{
	return area.getFields();
}
