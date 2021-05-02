// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <memory_resource>
#include <unordered_map>
#include <map>
#include <vector>

namespace clem
{
class AEntity;
class Archtype;
class Chunk;
struct EntityInfo;

class AScene
{
public:
	AEntity createEntity();
	void    destoryEntity(AEntity);

	void view(const Archtype&);
	
private:
	std::unordered_map<AEntity, EntityInfo> entities;
	std::vector<Archtype>                   archtypes;
	std::map<Archtype, Chunk*>              chunks; // unordered_map
	std::pmr::polymorphic_allocator<Chunk>  allocator;
};

} // namespace clem
