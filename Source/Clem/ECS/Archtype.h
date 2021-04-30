// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace clem
{
class Chunk;

class Archtype
{
public:
	Archtype(const std::set<std::type_index>&);

	bool operator==(const Archtype& rhs) const;

private:
	std::set<std::type_index> indexs;
};

} // namespace clem
