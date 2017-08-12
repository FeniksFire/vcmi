/*
 * CObstacleInstance.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "../BattleHex.h"
#include "ObstacleType.h"
#include "JsonNode.h"
#include "ObstacleArea.h"

class ObstacleJson;
class DLL_LINKAGE CObstacleInstance
{
public:
	ObstacleArea area;
	si32 uniqueID;
	si32 ID;

	CObstacleInstance();
	virtual ~CObstacleInstance();

	virtual ObstacleType getType() const;
	virtual ObstacleArea getArea() const;

	virtual const ObstacleJson getInfo() const;

	bool blocksTiles() const;
	bool stopsMovement() const;

	virtual bool visibleForSide(ui8 side, bool hasNativeStack) const;

	virtual void battleTurnPassed(){};

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & ID;
		h & area;
		h & uniqueID;
	}
};

class DLL_LINKAGE AbsoluteObstacle : public CObstacleInstance
{
public:
	virtual ObstacleType getType() const override;
	virtual const ObstacleJson getInfo() const override;
};

class DLL_LINKAGE MoatObstacle : public CObstacleInstance
{
public:
	virtual ObstacleType getType() const override;
};

class DLL_LINKAGE SpellCreatedObstacle : public CObstacleInstance
{
public:
	ObstacleType obstacleType;
	si8 turnsRemaining;
	si8 casterSpellPower;
	si8 spellLevel;
	si8 casterSide;
	si8 visibleForAnotherSide;

	SpellCreatedObstacle();

	virtual bool visibleForSide(ui8 side, bool hasNativeStack) const override;

	virtual ObstacleType getType() const override;
	virtual ObstacleArea getArea() const override;

	virtual void battleTurnPassed() override;

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & static_cast<CObstacleInstance&>(*this);
		h & turnsRemaining;
		h & casterSpellPower;
		h & spellLevel;
		h & obstacleType;
		h & casterSide;
		h & visibleForAnotherSide;
	}
};
