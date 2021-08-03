// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"
#include <algorithm>

namespace clem
{

Archtype::Archtype(std::set<TypeIndex>&& types)
		: types(std::move(types))
{
}

void Archtype::clear()
{
	types.clear();
}

bool Archtype::operator==(const Archtype& rhs) const
{
	return types == rhs.types;
}

bool Archtype::operator<(const Archtype& rhs) const
{
	return types < rhs.types;
}

/*
[[nodiscard]] size_t Archtype::hashCode() const
{
	size_t code = 0;
	for(auto type : types)
		code ^= type.hash_code();
	return code;
}
*/

} // namespace clem