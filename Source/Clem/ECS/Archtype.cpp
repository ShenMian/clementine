// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"

namespace clem
{

Archtype::Archtype(const std::set<std::type_index>& types)
		: indexs(types)
{
}

bool Archtype::operator==(const Archtype& rhs) const
{
	return indexs == rhs.indexs;
}

} // namespace clem
