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
#include "CTownHandler.h"
#include "VCMI_Lib.h"
#include "spells/CSpellHandler.h"
#include "filesystem/ResourceID.h"
#include "battle/obstacle/ObstacleJson.h"

CObstacleInstance::CObstacleInstance()
{
	offsetGraphicsInX = 0;
	offsetGraphicsInY = 0;

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
	offsetGraphicsInX = 0;
	offsetGraphicsInY = 0;
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
