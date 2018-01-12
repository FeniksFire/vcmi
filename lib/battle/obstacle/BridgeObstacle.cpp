/*
 * BridgeObstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "BridgeObstacle.h"

BridgeObstacle::BridgeObstacle(){}

BridgeObstacle::BridgeObstacle(ObstacleJson info, int16_t position) : StaticObstacle(info, position){}

ObstacleType BridgeObstacle::getType() const
{
	return ObstacleType::BRIDGE;
}

bool BridgeObstacle::blocksTiles() const
{
	return false;
}

bool BridgeObstacle::stopsMovement() const
{
	return false;
}
