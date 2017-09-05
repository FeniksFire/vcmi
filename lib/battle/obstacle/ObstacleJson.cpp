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

ObstacleType ObstacleJson::typeConvertFromString(std::string type) const
{
		if(type == "static")
			return ObstacleType::STATIC;
		else if(type == "moat")
			return ObstacleType::MOAT;
		else if(type == "firewall")
			return ObstacleType::FIRE_WALL;
		else if(type == "forcefield")
			return ObstacleType::FORCE_FIELD;
		else if(type == "landmine")
			return ObstacleType::LAND_MINE;
		else if(type == "quicksand")
			return ObstacleType::QUICKSAND;
}

ObstacleArea ObstacleJson::getArea() const
{
	ObstacleArea area;
	area.setArea(config["blockedTiles"].convertTo<std::vector<BattleHex>>());
	return area;
}

ObstacleSurface ObstacleJson::getSurface() const
{
	ObstacleSurface surface;
	surface.battlefieldSurface = config["battlefieldSurface"].convertTo<std::vector<BFieldType>>();
	return surface;
}

int32_t ObstacleJson::getOffsetGraphicsInY() const
{
	return config["offsetGraphicsInY"].Integer();
}

int32_t ObstacleJson::getOffsetGraphicsInX() const
{
	return config["offsetGraphicsInX"].Integer();
}

bool ObstacleJson::canBeRemovedBySpell() const
{
	return config["canBeRemoved"].Bool();
}

int16_t ObstacleJson::getPosition() const
{
	return config["position"].Integer();
}

std::vector<std::string> ObstacleJson::getPlace() const
{
	return config["place"].convertTo<std::vector<std::string>>();
}

int32_t ObstacleJson::getDamage() const
{
	return config["damage"].Integer();
}

int8_t ObstacleJson::getSpellLevel() const
{
	if(config["spellLevel"].isNull())
		return 1;
	return config["spellLevel"].Integer();
}

int32_t ObstacleJson::getSpellPower() const
{
	if(config["spellPower"].isNull())
		return 1;
	return config["spellPower"].Integer();
}

int8_t ObstacleJson::getBattleSide() const
{
	if(config["battleSide"].isNull())
		return 0;
	return config["battleSide"].Integer();
}

int8_t ObstacleJson::isVisibleForAnotherSide() const
{
	if(config["visibleForAnotherSide"].isNull())
		return 1;
	return config["visibleForAnotherSide"].Integer();
}

int16_t ObstacleJson::getTurnsRemaining() const
{
	if(config["turnsRemaining"].isNull())
		return -1;
	return config["turnsRemaining"].Integer();
}

ObstacleType ObstacleJson::getType() const
{
	return typeConvertFromString(config["type"].String());
}

std::string ObstacleJson::getGraphicsName() const
{
	return config["graphics"].String();
}

bool ObstacleJson::randomPosition() const
{
	return config["position"].isNull();
}

ObstacleJson::ObstacleJson(JsonNode jsonNode) : config(jsonNode)
{

}

ObstacleJson::ObstacleJson()
{

}
