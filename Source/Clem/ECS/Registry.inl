// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"

namespace clem
{

template <typename Com>
inline void Registry::each(std::function<void(const Entity&)> func)
{
	all([&](const Entity& entity) {
		if(entity.valid() && entity.anyOf<Com>())
			func(entity);
	});
}

template <typename Com>
inline void Registry::each(std::function<void(const Entity&, Com&)> func)
{
	each<Com>([&](const Entity& entity) {
		func(entity, getComponent<Com>(entity));
	});
}

// FIXME: 改变 Chunk 却没有转移 Components
template <typename Com, typename... Args>
inline Com& Registry::addComponent(const Entity& e, Args&&... args)
{
	auto& archtype = entities[e.id()].archtype;
	auto& chunk    = entities[e.id()].chunk;

	archtype.add<Com>();
	/*
	auto it = chunks.find(archtype);
	if(it == chunks.end())
	{
		chunk = new Chunk;
		// chunk = allocator.allocate(1);
		chunks.emplace(archtype, chunk);
	}
	else
		chunk = it->second;
	*/

	return chunk->addComponent<Com>(e, std::forward<Args>(args)...);
}

template <typename Com>
inline void Registry::removeComponent(const Entity& e)
{
	auto& archtype = entities[e.id()].archtype;
	auto& chunk    = entities[e.id()].chunk;

	chunk.removeComponent<Com>(e);

	/*
	auto it = chunks.find(archtype);
	if(it->second->empty())
	{
		delete it->second;
		// allocator.deallocate(it->second, 1);
		chunks.erase(it);
	}
	*/

	archtype.remove<Com>();
	/*
	it = chunks.find(archtype);
	if(it == chunks.end())
		chunk = chunks.emplace(archtype, allocator.allocate(1)); // �����µ� Chunk
	else
		chunk = it->second;
	*/
}

template <typename Com>
[[nodiscard]] inline Com& Registry::getComponent(const Entity& e)
{
	return entities[e.id()].chunk->getComponent<Com>(e);
}

template <typename... Coms>
[[nodiscard]] inline bool Registry::allOf(const Entity& e) const
{
	return entities[e.id()].archtype.all<Coms...>();
}

template <typename... Coms>
[[nodiscard]] inline bool Registry::anyOf(const Entity& e) const
{
	return entities[e.id()].archtype.any<Coms...>();
}

template <typename... Coms>
[[nodiscard]] inline bool Registry::noneOf(const Entity& e) const
{
	return entities[e.id()].archtype.none<Coms...>();
}

} // namespace clem