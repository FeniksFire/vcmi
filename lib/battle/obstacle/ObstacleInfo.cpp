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
	area.setArea(config["blockedTiles"].convertTo<std::vector<BattleHex>>());
	return area;
}

ObstacleSurface ObstacleInfo::getSurface() const
{
	ObstacleSurface surface;
	surface.areaSurface = config["allowedTerrain"].convertTo<std::vector<ETerrainType>>();
	surface.battlefieldSurface = config["specialBattlefields"].convertTo<std::vector<BFieldType>>();
	return surface;
}

int32_t ObstacleInfo::offsetGraphicsInY() const
{
	return config["offsetGraphicsInY"].Integer();
}

int32_t ObstacleInfo::offsetGraphicsInX() const
{
	return config["offsetGraphicsInX"].Integer();
}

int32_t ObstacleInfo::getPosition() const
{
	return config["position"].Integer();
}

std::string ObstacleInfo::getDefName() const
{
	return config["defname"].String();
}

ObstacleInfo::ObstacleInfo(JsonNode jsonNode) : config(jsonNode)
{

}

ObstacleInfo::ObstacleInfo()
{

}
