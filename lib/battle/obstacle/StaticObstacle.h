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
#include "ObstacleArea.h"

class ObstacleJson;

class DLL_LINKAGE StaticObstacle : public Obstacle
{
	ObstacleArea area;
	bool visible;
public:
	StaticObstacle();
	virtual ~StaticObstacle() {}

	virtual ObstacleType getType() const override;	
	virtual ObstacleArea getArea() const override;
	virtual void setArea(ObstacleArea obstacleArea) override;
	virtual bool isVisible() const override;

	void setVisibility(bool visual);
};
