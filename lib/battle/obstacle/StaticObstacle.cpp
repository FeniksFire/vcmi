/*
 * StaticObstacle.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StaticObstacle.h"

StaticObstacle::StaticObstacle()
{
	setVisibility(true);
}

ObstacleType StaticObstacle::getType() const
{
	return ObstacleType::STATIC;
}

void StaticObstacle::setVisibility(bool visual)
{
	visible = visual;
}

bool StaticObstacle::isVisible() const
{
	return visible;
}
