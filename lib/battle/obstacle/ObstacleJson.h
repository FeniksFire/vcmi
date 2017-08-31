/*
 * ObstacleJson.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "ObstacleArea.h"
#include "ObstacleSurface.h"
#include "JsonNode.h"

class DLL_LINKAGE ObstacleJson
{
private:
	JsonNode config;
public:
	virtual ObstacleArea getArea() const;
	virtual ObstacleSurface getSurface() const;
	virtual int32_t getOffsetGraphicsInY() const;
	virtual int32_t getOffsetGraphicsInX() const;
	virtual bool getCanBeRemovedBySpell() const;
	virtual int32_t getPosition() const;
	virtual std::string getGraphicsName() const;

	ObstacleJson(JsonNode jsonNode);
	ObstacleJson();
};
