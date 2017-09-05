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
#include "StaticObstacle.h".h"
#include "CTownHandler.h"
#include "VCMI_Lib.h"
#include "spells/CSpellHandler.h"
#include "filesystem/ResourceID.h"
#include "battle/obstacle/ObstacleJson.h"

bool StaticObstacle::canRemovedBySpell() const
{
	return canBeRemovedBySpell;
}

StaticObstacle::StaticObstacle()
{
	offsetGraphicsInX = 0;
	offsetGraphicsInY = 0;
}

StaticObstacle::StaticObstacle(ObstacleJson info, int16_t position)
{
	area = info.getArea();
	if(!info.randomPosition())
		position = info.getPosition();
	area.moveAreaToField(position);
	canBeRemovedBySpell = info.canBeRemovedBySpell();
	offsetGraphicsInY = info.getOffsetGraphicsInY();
	offsetGraphicsInX = info.getOffsetGraphicsInX();
	graphicsName = info.getGraphicsName();
}

StaticObstacle::~StaticObstacle()
{

}

ObstacleType StaticObstacle::getType() const
{
	return ObstacleType::STATIC;
}

ObstacleArea StaticObstacle::getArea() const
{
	return area;
}


bool StaticObstacle::visibleForSide(ui8 side, bool hasNativeStack) const
{
	return true;
}

void StaticObstacle::battleTurnPassed()
{

}

ObstacleType MoatObstacle::getType() const
{
	return ObstacleType::MOAT;
}

MoatObstacle::MoatObstacle()
{

}

MoatObstacle::MoatObstacle(ObstacleJson info)
{
	area = info.getArea();
	area.moveAreaToField(info.getPosition());
	damage = info.getDamage();
	offsetGraphicsInX = info.getOffsetGraphicsInX();
	offsetGraphicsInY = info.getOffsetGraphicsInY();
	graphicsName = info.getGraphicsName();;
	canBeRemovedBySpell = info.canBeRemovedBySpell();;
}
