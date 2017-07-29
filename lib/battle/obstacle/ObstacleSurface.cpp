/*
 * ObstacleSurface.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "ObstacleSurface.h"

bool ObstacleSurface::isAppropriateForSurface(ETerrainType terrainType, BFieldType battlefieldType) const
{
	if(battlefieldType != BFieldType::NONE)
		return vstd::contains(battlefieldSurface, battlefieldType);
	return vstd::contains(areaSurface, terrainType);
}
