// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"

namespace clem
{

Archtype::Archtype(std::vector<std::type_info>& types)
{
	for(auto& t : types)
		indexs.insert(std::type_index(t));
}

} // namespace clem
