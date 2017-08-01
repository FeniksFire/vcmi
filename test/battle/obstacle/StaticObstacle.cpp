/*
 * StaticObstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "../lib/battle/obstacle/StaticObstacle.h"

class StaticObstacleTest : public ::testing::Test
{
public:
	StaticObstacle obstacle;
};


TEST_F(StaticObstacleTest, initialValues)
{
	EXPECT_EQ(obstacle.getType(), ObstacleType::STATIC);
	EXPECT_TRUE(obstacle.isVisible());
	EXPECT_TRUE(obstacle.getArea().getFields().empty());
}

TEST_F(StaticObstacleTest, getArea)
{
	ObstacleArea area;
	area.addField(103);
	area.addField(122);
	area.addField(103);
	area.addField(122);
	obstacle.setArea(area);
	EXPECT_EQ(obstacle.getArea().getFields().size(), 2);
	EXPECT_EQ(obstacle.getArea().getFields().at(0), 103);
	EXPECT_EQ(obstacle.getArea().getFields().at(1), 122);
}

