/*
 * ObstacleGraphicsInfo.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "ObstacleGraphicsInfo.h"

ObstacleGraphicsInfo::ObstacleGraphicsInfo()
{

}

void ObstacleGraphicsInfo::setGraphicsName(std::string name)
{
	graphicsName = name;
}

void ObstacleGraphicsInfo::setOffsetGraphicsInX(int32_t value)
{
	offsetGraphicsInX = value;
}

void ObstacleGraphicsInfo::setOffsetGraphicsInY(int32_t value)
{
	offsetGraphicsInY = value;
}

std::string ObstacleGraphicsInfo::getGraphicsName() const
{
	return graphicsName;
}

int32_t ObstacleGraphicsInfo::getOffsetGraphicsInX() const
{
	return offsetGraphicsInX;
}

int32_t ObstacleGraphicsInfo::getOffsetGraphicsInY() const
{
	return offsetGraphicsInY;
}

