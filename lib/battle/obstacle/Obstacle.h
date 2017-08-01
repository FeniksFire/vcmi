/*
 * Obstacle.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "ObstacleType.h"
#include "ObstacleArea.h"

class ObstacleInfo;

class DLL_LINKAGE Obstacle
{
protected:
	ObstacleArea area;
public:
	virtual ~Obstacle() {}
	virtual ObstacleType getType() const = 0;
	virtual ObstacleArea getArea() const;
	virtual void setArea(ObstacleArea obstacleArea);
	virtual bool isVisible() const = 0;
};
