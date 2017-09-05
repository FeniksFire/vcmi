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

class DLL_LINKAGE Obstacle
{
private:
	boost::uuids::uuid generateID();
	boost::uuids::uuid ID = generateID();
public:
	boost::uuids::uuid getID() const;

	virtual ~Obstacle() {}
	virtual ObstacleType getType() const = 0;
	virtual ObstacleArea getArea() const = 0;
	virtual bool visibleForSide(ui8 side, bool hasNativeStack) const = 0;
	virtual bool canRemovedBySpell() const = 0;
	virtual void battleTurnPassed() = 0;
	bool blocksTiles() const;
	bool stopsMovement() const;

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & ID;
	}
};
