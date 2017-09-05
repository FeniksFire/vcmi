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
#include "ObstacleType.h"
#include "JsonNode.h"

class DLL_LINKAGE ObstacleJson
{
private:
	ObstacleType typeConvertFromString(std::string type) const;
protected:
	JsonNode config;
public:
	virtual ObstacleArea getArea() const;
	virtual ObstacleSurface getSurface() const;
	virtual int32_t getOffsetGraphicsInY() const;
	virtual int32_t getOffsetGraphicsInX() const;
	virtual bool canBeRemovedBySpell() const;
	virtual int16_t getPosition() const;
	virtual std::vector<std::string> getPlace() const;
	virtual int32_t getDamage() const;

	virtual int8_t getSpellLevel() const;
	virtual int32_t getSpellPower() const;
	virtual int8_t getBattleSide() const;
	virtual int8_t isVisibleForAnotherSide() const;
	virtual int16_t getTurnsRemaining() const;

	virtual ObstacleType getType() const;
	virtual std::string getGraphicsName() const;
	virtual bool randomPosition() const;
	ObstacleJson(JsonNode jsonNode);
	ObstacleJson();
};
