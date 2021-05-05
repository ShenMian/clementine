// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"
#include <algorithm>

namespace clem
{
Archtype::Archtype(const type_set& types)
		: types(types)
{
}

bool Archtype::all(const Archtype& ts) const
{
	for(auto& t : ts.types)
		if(types.find(t) == types.end())
			return false;
	return true;
}

bool Archtype::any(const Archtype& ts) const
{
	for(auto& t : ts.types)
		if(types.find(t) != types.end())
			return true;
	return false;
}

bool Archtype::none(const Archtype& ts) const
{
	return !any(ts);
}

bool Archtype::operator==(const Archtype& rhs) const
{
	return types == rhs.types;
}

bool Archtype::operator<(const Archtype& rhs) const
{
	return types < rhs.types;
}
} // namespace clem