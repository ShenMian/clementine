// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"
#include <algorithm>

namespace clem
{
template <typename T, typename... Types>
bool Archtype<T, Types...>::all(const Archtype& ts) const
{
	for(auto& t : ts.types)
		if(types.find(t) == types.end())
			return false;
	return true;
}

template <typename T, typename... Types>
bool Archtype<T, Types...>::any(const Archtype& ts) const
{
	for(auto& t : ts.types)
		if(types.find(t) != types.end())
			return true;
	return false;
}

template <typename T, typename... Types>
bool Archtype<T, Types...>::none(const Archtype& ts) const
{
	return !any(ts);
}

template <typename T, typename... Types>
bool Archtype<T, Types...>::operator==(const Archtype& rhs) const
{
	return types == rhs.types;
}

template <typename T, typename... Types>
bool Archtype<T, Types...>::operator<(const Archtype& rhs) const
{
	return types < rhs.types;
}
} // namespace clem