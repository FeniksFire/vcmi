/*
 * mock_ObstacleJson.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "StdInc.h"
#include "lib/battle/obstacle/ObstacleJson.h"

class ObstacleJsonMock : public ObstacleJson
{
public:
	MOCK_CONST_METHOD0(getArea, ObstacleArea());
	MOCK_CONST_METHOD0(getSurface, ObstacleSurface());
	MOCK_CONST_METHOD0(getHeight, int32_t());
	MOCK_CONST_METHOD0(getWidth, int32_t());
	MOCK_CONST_METHOD0(getGraphicsName, std::string());
};
