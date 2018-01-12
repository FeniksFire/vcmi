/*
 * BridgeObstacle.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "StaticObstacle.h"


class DLL_LINKAGE BridgeObstacle : public StaticObstacle
{
public:
	BridgeObstacle();
	BridgeObstacle(ObstacleJson info, int16_t position = 0);
	ObstacleType getType() const override;
	bool blocksTiles() const override;
	bool stopsMovement() const override;

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & static_cast<StaticObstacle&>(*this);
	}
};
