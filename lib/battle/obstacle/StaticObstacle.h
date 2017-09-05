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
#include "../BattleHex.h"
#include "ObstacleJson.h"
#include "Obstacle.h"

class ObstacleJson;

class DLL_LINKAGE StaticObstacle : public Obstacle
{
public:
	ObstacleArea area;
	int32_t offsetGraphicsInY;
	int32_t offsetGraphicsInX;
	std::string graphicsName;

	bool canBeRemovedBySpell = 0;
	virtual bool canRemovedBySpell() const;
	StaticObstacle();
	StaticObstacle(ObstacleJson info, int16_t position = 0);
	virtual ~StaticObstacle();

	virtual ObstacleType getType() const;
	virtual ObstacleArea getArea() const;

	virtual bool visibleForSide(ui8 side, bool hasNativeStack) const;

	virtual void battleTurnPassed();

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & static_cast<Obstacle&>(*this);
		h & offsetGraphicsInX;
		h & offsetGraphicsInY;
		h & canBeRemovedBySpell;
		h & graphicsName;
		h & area;
	}
};

class DLL_LINKAGE MoatObstacle : public StaticObstacle
{
public:
	int32_t damage = 0;
	virtual ObstacleType getType() const override;
	MoatObstacle();
	MoatObstacle(ObstacleJson info);
	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & static_cast<StaticObstacle&>(*this);
		h & damage;
	}
};
