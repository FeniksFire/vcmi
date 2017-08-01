/*
 * ObstacleArea.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "lib/battle/obstacle/ObstacleArea.h"
#include "lib/battle/BattleHex.h"

class ObstacleAreaTest : public ::testing::Test
{
public:
	ObstacleArea area;
};

TEST_F(ObstacleAreaTest, getInitialArea)
{
	EXPECT_EQ(area.position, 0);
	EXPECT_TRUE(area.getFields().empty());
}

TEST_F(ObstacleAreaTest, getFields)
{
	area.addField(BattleHex(12));
	EXPECT_EQ(area.getFields().size(), 1);
	area.addField(BattleHex(12));
	EXPECT_EQ(area.getFields().size(), 1);
	EXPECT_EQ(area.getFields().at(0), BattleHex(12));
}

TEST_F(ObstacleAreaTest, moveAreaToField)
{
	std::vector<BattleHex> fields{103, 104, 122, 138, 137, 120};

	area.setArea(fields);
	area.position = 121;
	area.moveAreaToField(44);

	EXPECT_EQ(area.position, 44);
	EXPECT_EQ(area.getFields().size(), 6);
	EXPECT_EQ(area.getFields().at(0), 27);
	EXPECT_EQ(area.getFields().at(1), 28);
	EXPECT_EQ(area.getFields().at(2), 45);
	EXPECT_EQ(area.getFields().at(3), 62);
	EXPECT_EQ(area.getFields().at(4), 61);
	EXPECT_EQ(area.getFields().at(5), 43);

	area.moveAreaToField(61);

	EXPECT_EQ(area.getFields().at(0), 43);
	EXPECT_EQ(area.getFields().at(1), 44);
	EXPECT_EQ(area.getFields().at(2), 62);
	EXPECT_EQ(area.getFields().at(3), 78);
	EXPECT_EQ(area.getFields().at(4), 77);
	EXPECT_EQ(area.getFields().at(5), 60);

	area.moveAreaToField(19);

	EXPECT_EQ(area.getFields().at(0), 1);
	EXPECT_EQ(area.getFields().at(1), 2);
	EXPECT_EQ(area.getFields().at(2), 20);
	EXPECT_EQ(area.getFields().at(3), 36);
	EXPECT_EQ(area.getFields().at(4), 35);
	EXPECT_EQ(area.getFields().at(5), 18);

	fields.clear();
	fields = {2, 19, 35, 52};

	area.setArea(fields);
	area.position = 130;
	area.moveAreaToField(146);

	EXPECT_EQ(area.getFields().at(0), 19);
	EXPECT_EQ(area.getFields().at(1), 35);
	EXPECT_EQ(area.getFields().at(2), 52);
	EXPECT_EQ(area.getFields().at(3), 68);

	fields.clear();
	fields = {74, 58, 40, 24};

	area.setArea(fields);
	area.position = 74;
	area.moveAreaToField(127);

	EXPECT_EQ(area.getFields().at(0), 127);
	EXPECT_EQ(area.getFields().at(1), 110);
	EXPECT_EQ(area.getFields().at(2), 93);
	EXPECT_EQ(area.getFields().at(3), 76);
}


