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

CObstacleInstance::CObstacleInstance()
{
	uniqueID = -1;
	ID = -1;
}

CObstacleInstance::~CObstacleInstance()
{

}

ObstacleType CObstacleInstance::getType() const
{
	return ObstacleType::USUAL;
}

const ObstacleInfo CObstacleInstance::getInfo() const
{
	return ObstacleInfo(JsonNode(ResourceID("config/obstacles.json"))["obstacles"].Vector().at(ID));
}

ObstacleArea CObstacleInstance::getArea() const
{
	return area;
}


bool CObstacleInstance::visibleForSide(ui8 side, bool hasNativeStack) const
{
	return true;
}

bool CObstacleInstance::stopsMovement() const
{
	return getType() == ObstacleType::QUICKSAND || getType() == ObstacleType::MOAT;
}

bool CObstacleInstance::blocksTiles() const
{
	return getType() == ObstacleType::USUAL || getType() == ObstacleType::ABSOLUTE_OBSTACLE || getType() == ObstacleType::FORCE_FIELD;
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
	switch(getType())
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

ObstacleType SpellCreatedObstacle::getType() const
{
	return obstacleType;
}

ObstacleArea SpellCreatedObstacle::getArea() const
{
	ObstacleArea ret;
	ret = area;
	switch(getType())
	{
	case ObstacleType::QUICKSAND:
	case ObstacleType::LAND_MINE:
	case ObstacleType::FIRE_WALL:
		ret.setArea(std::vector<BattleHex>(1, area.position));
		break;
	case ObstacleType::FORCE_FIELD:
		ret.setArea(SpellID(SpellID::FORCE_FIELD).toSpell()->rangeInHexes(area.position, spellLevel, casterSide));
		break;
	default:
		assert(0);
		ret.setArea(std::vector<BattleHex>());
	}
	return ret;
}

void SpellCreatedObstacle::battleTurnPassed()
{
	if(turnsRemaining > 0)
		turnsRemaining--;
}

ObstacleType MoatObstacle::getType() const
{
	return ObstacleType::MOAT;
}

ObstacleType AbsoluteObstacle::getType() const
{
	return ObstacleType::ABSOLUTE_OBSTACLE;
}

const ObstacleInfo AbsoluteObstacle::getInfo() const
{
	return ObstacleInfo(JsonNode(ResourceID("config/obstacles.json"))["absoluteObstacles"].Vector().at(ID));
}
