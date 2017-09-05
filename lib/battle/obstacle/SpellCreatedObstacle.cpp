/*
 * StaticObstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "SpellCreatedObstacle.h"
#include "CTownHandler.h"
#include "VCMI_Lib.h"
#include "spells/CSpellHandler.h"
#include "filesystem/ResourceID.h"
#include "battle/obstacle/ObstacleJson.h"

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

SpellCreatedObstacle::SpellCreatedObstacle(ObstacleJson info)
{
	offsetGraphicsInX = info.getOffsetGraphicsInX();
	offsetGraphicsInY = info.getOffsetGraphicsInY();
	area = info.getArea();
	area.moveAreaToField(info.getPosition());
	spellLevel = info.getSpellLevel();
	graphicsName = info.getGraphicsName();;
	turnsRemaining = info.getTurnsRemaining();
	casterSpellPower = info.getSpellPower();
	visibleForAnotherSide = info.isVisibleForAnotherSide();
	casterSide = info.getBattleSide();
}

bool SpellCreatedObstacle::visibleForSide(ui8 side, bool hasNativeStack) const
{
	switch(getType())
	{
	case ObstacleType::FIRE_WALL:
	case ObstacleType::FORCE_FIELD:
		return visibleForAnotherSide;
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
