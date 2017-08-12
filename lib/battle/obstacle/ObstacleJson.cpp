/*
 * ObstacleJson.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "ObstacleJson.h"

ObstacleArea ObstacleJson::getArea() const
{
	ObstacleArea area;
	area.setArea(config["blockedTiles"].convertTo<std::vector<BattleHex>>());
	return area;
}

ObstacleSurface ObstacleJson::getSurface() const
{
	ObstacleSurface surface;
	surface.areaSurface = config["allowedTerrain"].convertTo<std::vector<ETerrainType>>();
	surface.battlefieldSurface = config["specialBattlefields"].convertTo<std::vector<BFieldType>>();
	return surface;
}

int32_t ObstacleJson::offsetGraphicsInY() const
{
	return config["offsetGraphicsInY"].Integer();
}

int32_t ObstacleJson::offsetGraphicsInX() const
{
	return config["offsetGraphicsInX"].Integer();
}

int32_t ObstacleJson::getPosition() const
{
	return config["position"].Integer();
}

std::string ObstacleJson::getDefName() const
{
	return config["defname"].String();
}

ObstacleJson::ObstacleJson(JsonNode jsonNode) : config(jsonNode)
{

}

ObstacleJson::ObstacleJson()
{

}
