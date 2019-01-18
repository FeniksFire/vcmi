/*
 * UUID.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

class DLL_LINKAGE UUID
{
public:
	boost::uuids::uuid getID() const;
	
	bool operator==(const UUID &rhs) const;
	
	bool operator!=(const UUID &rhs) const;
	
	template <typename Handler> void serialize(Handler &h, const int version)
	{
		h & ID;
	}
private:
	boost::uuids::uuid ID = generateID();
	static boost::uuids::uuid generateID();
};
