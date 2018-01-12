/*
 * GateObstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "GateObstacle.h"

GateObstacle::GateObstacle(){}

GateObstacle::GateObstacle(ObstacleJson info, int16_t position) : BridgeObstacle(info, position)
{
}

ObstacleType GateObstacle::getType() const
{
	return ObstacleType::GATE;
}

bool GateObstacle::blocksTiles() const
{
	if(isOpen())
		return false;
	else
		return true;
}

bool GateObstacle::stopsMovement() const
{
	return false;
}

bool GateObstacle::isOpen() const
{
	return state == EGateState::OPENED;
}

bool GateObstacle::canUseGate() const
{

}

void GateObstacle::setState(EGateState gateState)
{
	state = gateState;
}

EGateState GateObstacle::getState() const
{
	return state;
}
