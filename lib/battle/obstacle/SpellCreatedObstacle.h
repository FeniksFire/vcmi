/*
 * SpellCreatedObstacle.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "Obstacle.h"
#include "ObstacleJson.h"

class DLL_LINKAGE SpellCreatedObstacle : public Obstacle
{
public:
	ObstacleType obstacleType;
	int32_t turnsRemaining;
	int32_t casterSpellPower;
	int8_t spellLevel;
	int8_t casterSide;
	bool visibleForAnotherSide = true;

	SpellCreatedObstacle();
	SpellCreatedObstacle(ObstacleJson info);

	virtual bool canRemovedBySpell(int8_t levelOfSpellRemoval) const override;
	virtual bool visibleForSide(ui8 side, bool hasNativeStack) const override;
	virtual ObstacleType getType() const override;

	virtual void battleTurnPassed() override;

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & static_cast<Obstacle&>(*this);
		h & turnsRemaining;
		h & casterSpellPower;
		h & spellLevel;
		h & obstacleType;
		h & casterSide;
		h & visibleForAnotherSide;
	}
};

