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

	int getWidth();
	int getHeight();


	std::vector<BattleHex> getFields() const;
	ObstacleArea();

	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & area;
		h & position;
	}
};
