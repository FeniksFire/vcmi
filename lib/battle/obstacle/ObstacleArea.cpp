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
#include "ObstacleArea.h"

void ObstacleArea::addField(BattleHex field)
{
	if(!vstd::contains(area, field))
		area.push_back(field);
}

void ObstacleArea::setArea(std::vector<BattleHex> fields)
{
	area.clear();
	for(auto &i : fields)
		addField(i);
}

std::vector<BattleHex> ObstacleArea::getArea() const
{
	return area;
}

std::vector<BattleHex> ObstacleArea::getMovedArea(BattleHex offset) const
{
	ObstacleArea moved;
	moved.setArea(area);
	moved.moveAreaToField(offset);
	return moved.getArea();
}

void ObstacleArea::moveAreaToField(BattleHex offset)
{
	if(position == offset)
		return;
	for(auto &field : area)
	{
		field.hex += offset.hex - position;
		if(position.getY() % 2 != offset.getY() % 2){
			if(offset.getY() % 2 == 0 && field.getY() % 2 == 1)
				field.moveInDirection(BattleHex::RIGHT);
			if(offset.getY() % 2 == 1 && field.getY() % 2 == 0)
				field.moveInDirection(BattleHex::LEFT);
		}
	}
	position = offset;
}

ObstacleArea::ObstacleArea()
{
	position = 0;
}
