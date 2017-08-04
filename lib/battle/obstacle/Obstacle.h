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
public:
	virtual ~Obstacle() {}
	virtual ObstacleType getType() const = 0;
	virtual ObstacleArea getArea() const = 0;
	virtual void setArea(ObstacleArea obstacleArea) = 0;
	virtual bool isVisible() const = 0;

};
