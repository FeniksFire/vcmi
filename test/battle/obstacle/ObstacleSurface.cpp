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
	EXPECT_FALSE(terrain.isAppropriateForSurface(BFieldType::ROCKLANDS));
	terrain.battlefieldSurface.push_back(BFieldType::SAND_SHORE);
	terrain.battlefieldSurface.push_back(BFieldType::SHIP);
	EXPECT_TRUE(terrain.isAppropriateForSurface(BFieldType::SAND_SHORE));
	EXPECT_TRUE(terrain.isAppropriateForSurface(BFieldType::SHIP));
	EXPECT_FALSE(terrain.isAppropriateForSurface(BFieldType::SHIP_TO_SHIP));
}
