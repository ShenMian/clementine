// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <vector>
#include <memory_resource>
#include <typeindex>
#include <typeinfo>

namespace clem
{
class Chunk;

class Archtype
{
public:
	Archtype(std::vector<std::type_info>&);

private:
	std::set<std::type_index> indexs;

	//std::vector<Chunk*>                    chunks;
	//std::pmr::polymorphic_allocator<Chunk> allocator;
};

} // namespace clem
