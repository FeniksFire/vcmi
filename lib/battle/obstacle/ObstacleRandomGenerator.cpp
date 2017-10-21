/*
 * ObstacleRandomGenerator.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "ObstacleRandomGenerator.h"
#include "JsonNode.h"
#include "ObstacleJson.h"
#include "filesystem/ResourceID.h"


std::vector<int> ObstacleRandomGenerator::getIndexesFromTerrainBattles(bool canBeRemovedBySpell)
{
	std::vector<int> indexes;
	const JsonNode obstacleConfig(ResourceID("config/obstacles.json"));
	for(int i = 0; i < obstacleConfig["obstacles"].Vector().size(); i++)
	{
		auto info = ObstacleJson(obstacleConfig["obstacles"].Vector().at(i));
		if(canBeRemovedBySpell == info.canBeRemovedBySpell() && info.getPlace().empty())
				indexes.push_back(i);
	}
	return indexes;
}

ObstacleRandomGenerator::ObstacleRandomGenerator(int3 worldMapTile)
{
	r.srand(worldMapTile);
	r.rand(1,8);
}

void ObstacleRandomGenerator::randomTilesAmountToBlock(int min, int max)
{
	setTilesAmountToBlock(r.rand(min, max));
}

void ObstacleRandomGenerator::setTilesAmountToBlock(int amount)
{
	tilesToBlock = amount;
}

int ObstacleRandomGenerator::getTilesAmountToBlock()
{
	return tilesToBlock;
}
