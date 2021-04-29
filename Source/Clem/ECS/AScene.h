// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <memory_resource>
#include <unordered_map>
#include <vector>

namespace clem
{
class AEntity;
class Archtype;
class Chunk;

class AScene
{
public:
	AEntity createEntity();
	void    destoryEntity(AEntity);
	
private:
	std::vector<Archtype> archtypes;
	std::unordered_map<Archtype, Chunk*> chunks;
	std::pmr::polymorphic_allocator<Chunk> allocator;
};

} // namespace clem
