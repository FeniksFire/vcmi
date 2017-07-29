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
	EXPECT_TRUE(area.getArea().empty());
}

TEST_F(ObstacleAreaTest, getArea)
{
	area.addField(BattleHex(12));
	EXPECT_EQ(area.getArea().size(), 1);
	area.addField(BattleHex(12));
	EXPECT_EQ(area.getArea().size(), 1);
	EXPECT_EQ(area.getArea().at(0), BattleHex(12));
}

TEST_F(ObstacleAreaTest, moveAreaToField)
{
	std::vector<BattleHex> fields;
	fields.push_back(103);
	fields.push_back(104);
	fields.push_back(122);
	fields.push_back(138);
	fields.push_back(137);
	fields.push_back(120);

	area.setArea(fields);
	area.position = 121;
	area.moveAreaToField(44);

	EXPECT_EQ(area.position, 44);
	EXPECT_EQ(area.getArea().size(), 6);
	EXPECT_EQ(area.getArea().at(0), 27);
	EXPECT_EQ(area.getArea().at(1), 28);
	EXPECT_EQ(area.getArea().at(2), 45);
	EXPECT_EQ(area.getArea().at(3), 62);
	EXPECT_EQ(area.getArea().at(4), 61);
	EXPECT_EQ(area.getArea().at(5), 43);

	area.moveAreaToField(61);

	EXPECT_EQ(area.getArea().at(0), 43);
	EXPECT_EQ(area.getArea().at(1), 44);
	EXPECT_EQ(area.getArea().at(2), 62);
	EXPECT_EQ(area.getArea().at(3), 78);
	EXPECT_EQ(area.getArea().at(4), 77);
	EXPECT_EQ(area.getArea().at(5), 60);

	area.moveAreaToField(19);

	EXPECT_EQ(area.getArea().at(0), 1);
	EXPECT_EQ(area.getArea().at(1), 2);
	EXPECT_EQ(area.getArea().at(2), 20);
	EXPECT_EQ(area.getArea().at(3), 36);
	EXPECT_EQ(area.getArea().at(4), 35);
	EXPECT_EQ(area.getArea().at(5), 18);

	fields.clear();
	fields.push_back(2);
	fields.push_back(19);
	fields.push_back(35);
	fields.push_back(52);

	area.setArea(fields);
	area.position = 130;
	area.moveAreaToField(146);

	EXPECT_EQ(area.getArea().at(0), 19);
	EXPECT_EQ(area.getArea().at(1), 35);
	EXPECT_EQ(area.getArea().at(2), 52);
	EXPECT_EQ(area.getArea().at(3), 68);

	fields.clear();
	fields.push_back(74);
	fields.push_back(58);
	fields.push_back(40);
	fields.push_back(24);

	area.setArea(fields);
	area.position = 74;
	area.moveAreaToField(127);

	EXPECT_EQ(area.getArea().at(0), 127);
	EXPECT_EQ(area.getArea().at(1), 110);
	EXPECT_EQ(area.getArea().at(2), 93);
	EXPECT_EQ(area.getArea().at(3), 76);
}


