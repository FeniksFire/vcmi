/*
 * ObstacleArea.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "../BattleHex.h"

class DLL_LINKAGE ObstacleArea
{
	std::vector<BattleHex> area;
public:
	BattleHex position;

	void addField(BattleHex field);
	void setArea(std::vector<BattleHex> fields);
	void moveAreaToField(BattleHex offset);

	std::vector<BattleHex> getArea() const;
	std::vector<BattleHex> getMovedArea(BattleHex offset) const;

	ObstacleArea();
};
