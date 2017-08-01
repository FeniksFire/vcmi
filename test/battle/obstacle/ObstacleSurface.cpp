/*
 * ObstacleSurface.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "lib/battle/obstacle/ObstacleSurface.h"

TEST(ObstacleSurfaceTest, isAppropriateForSurface)
{
	ObstacleSurface terrain;
	terrain.areaSurface.push_back(ETerrainType::GRASS);
	terrain.areaSurface.push_back(ETerrainType::LAVA);
	terrain.areaSurface.push_back(ETerrainType::ROCK);
	terrain.areaSurface.push_back(ETerrainType::SAND);
	EXPECT_TRUE(terrain.isAppropriateForSurface(ETerrainType::ROCK));
	EXPECT_FALSE(terrain.isAppropriateForSurface(ETerrainType::WATER));
	terrain.battlefieldSurface.push_back(BFieldType::GRASS_HILLS);
	terrain.battlefieldSurface.push_back(BFieldType::MAGIC_PLAINS);
	terrain.battlefieldSurface.push_back(BFieldType::ROCKLANDS);
	terrain.battlefieldSurface.push_back(BFieldType::SAND_SHORE);
	EXPECT_TRUE(terrain.isAppropriateForSurface(ETerrainType::WATER, BFieldType::SAND_SHORE));
	EXPECT_FALSE(terrain.isAppropriateForSurface(ETerrainType::WATER, BFieldType::SHIP));
}
