/*
 * ObstacleRandomGenerator.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include "battle/RangeGenerator.h"
#include "battle/RandGen.h"

class DLL_LINKAGE ObstacleRandomGenerator
{	
public:
	RandGen r;
	std::vector<int> getIndexesFromTerrainBattles(bool canBeRemovedBySpell);
	int randomTilesAmountToBlock(int min, int max);

	ObstacleRandomGenerator(int3 worldMapTile);
};
