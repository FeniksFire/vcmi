/*
 * StaticObstacle.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "Obstacle.h"

class ObstacleInfo;

class DLL_LINKAGE StaticObstacle : public Obstacle
{
	bool visible;
public:
	StaticObstacle();
	virtual ~StaticObstacle() {}
	virtual ObstacleType getType() const override;	
	void setVisibility(bool visual);
	virtual bool isVisible() const override;

};
