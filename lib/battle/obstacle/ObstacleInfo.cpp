/*
 * ObstacleInfo.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "ObstacleInfo.h"

ObstacleArea ObstacleInfo::getArea() const
{
	ObstacleArea area;
	area.setArea(node["blockedTiles"].convertTo<std::vector<BattleHex>>());
	return area;
}

ObstacleSurface ObstacleInfo::getSurface() const
{
	ObstacleSurface surface;
	surface.areaSurface = node["allowedTerrain"].convertTo<std::vector<ETerrainType>>();
	surface.battlefieldSurface = node["specialBattlefields"].convertTo<std::vector<BFieldType>>();
	return surface;
}

int32_t ObstacleInfo::getHeight() const
{
	return node["height"].Integer();
}

int32_t ObstacleInfo::getWidth() const
{
	return node["width"].Integer();
}

int32_t ObstacleInfo::getID() const
{
	return node["id"].Integer();
}

std::string ObstacleInfo::getDefName() const
{
	return node["defname"].String();
}

ObstacleInfo::ObstacleInfo(JsonNode jsonNode) : node(jsonNode)
{

}
