/*
 * MoatObstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "MoatObstacle.h"

ObstacleType MoatObstacle::getType() const
{
	return ObstacleType::MOAT;
}

MoatObstacle::MoatObstacle()
{

}

MoatObstacle::MoatObstacle(ObstacleJson info, int16_t position)
{
	if(!info.randomPosition())
		position = info.getPosition();
	setArea(ObstacleArea(info.getArea(), position));
	setDamage(info.getDamage());
	setGraphicsInfo(info.getGraphicsInfo());
	canBeRemovedBySpell = info.canBeRemovedBySpell();;
}

int32_t MoatObstacle::getDamage() const
{
	return damage;
}

void MoatObstacle::setDamage(int32_t value)
{
	damage = value;
}
