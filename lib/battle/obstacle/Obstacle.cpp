/*
 * Obstacle.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "Obstacle.h"

boost::uuids::uuid Obstacle::generateID()
{
	static boost::uuids::random_generator gen(new boost::mt19937);
	return gen();
}

boost::uuids::uuid Obstacle::getID() const
{
	return ID;
}

bool Obstacle::stopsMovement() const
{
	return getType() == ObstacleType::QUICKSAND || getType() == ObstacleType::MOAT;
}

bool Obstacle::blocksTiles() const
{
	return getType() == ObstacleType::STATIC || getType() == ObstacleType::FORCE_FIELD;
}
