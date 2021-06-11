// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AEntity.h"
#include "Archtype.h"
#include <cstdint>
#include <map>
#include <memory_resource>
#include <unordered_map>
#include <vector>

namespace clem
{
class Chunk;

struct EntityInfo
{
	Archtype                         archtype;
	std::map<std::type_index, void*> components;
};

class AScene
{
public:
	AEntity createEntity();
	void    destoryEntity(AEntity);

	template <typename Com, typename... Args>
	Com& createComponent(AEntity entity, Args&&... args);

	template <typename Com>
	void destoryComponent();

	void view(const Archtype&);

private:
	// std::map<AEntity, EntityInfo>          entities;
	std::vector<Archtype> archtypes;
	// std::map<Archtype, Chunk*>             chunks; // unordered_map
	std::pmr::polymorphic_allocator<Chunk> allocator;
};

template <typename Com, typename... Args>
Com& AScene::createComponent(AEntity entity, Args&&... args)
{
	// auto  it   = entities.find(entity);
	// auto& info = entities.find(entity)->second;
	// change archtype and move component to other chunk
	// info.components.emplace(typeid(Com), std::move(Com(Args)));
}

template <typename Com>
void AScene::destoryComponent()
{
	// auto  it   = entities.find(entity);
	// auto& info = entities.find(entity)->second;
	// info.components.erase(info.components.find(typeid(Com)));
}
} // namespace clem
