// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"
#include <algorithm>

namespace clem
{
Archtype::Archtype(std::set<std::type_index>&& types)
		: types(std::move(types))
{
}

bool Archtype::operator==(const Archtype& rhs) const
{
	return types == rhs.types;
}

bool Archtype::operator<(const Archtype& rhs) const
{
	return types < rhs.types;
}

size_t Archtype::getHashCode() const
{
	size_t code = 0;
	for(auto type : types)
		code ^= type.hash_code();
	return code;
}

} // namespace clem
