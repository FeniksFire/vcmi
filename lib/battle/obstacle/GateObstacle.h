/*
 * GateObstacle.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "BridgeObstacle.h"
#pragma once

class DLL_LINKAGE GateObstacle : public BridgeObstacle
{
public:
	GateObstacle();
	GateObstacle(ObstacleJson info, int16_t position = 0);
	ObstacleType getType() const override;
	bool blocksTiles() const override;
	bool stopsMovement() const override;

	bool isOpen() const;
	void setState(EGateState gateState);
	EGateState getState() const;
	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & static_cast<BridgeObstacle&>(*this);
		h & state;
	}
protected:
	EGateState state = EGateState::NONE;
};
