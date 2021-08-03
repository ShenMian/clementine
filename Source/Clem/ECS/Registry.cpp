// Copyright 2021 SMS
// License(Apache-2.0)

#include "Registry.h"
#include "Archtype.h"
#include "Chunk.h"
#include "Components/Tag.h"
#include "Core/Core.h"
#include "System.h"
#include <algorithm>
#include <cassert>
#include <ranges>

namespace clem
{

[[nodiscard]] Entity Registry::create()
{
	const auto id      = requestId();
	entities[id].chunk = &chunk;
	return Entity(id, entities[id].version, *this);
}

[[nodiscard]] Entity Registry::create(const std::string& tag)
{
	auto entity = create();
	entity.add<Tag>(tag);
	return entity;
}

void Registry::destroy(const Entity& e)
{
	const auto id = e.id();
	assert(entities[id].version < std::numeric_limits<version_type>::max());
	entities[id].version++;
	entities[id].archtype.clear();
	recycleId(id);
}

[[nodiscard]] Entity Registry::get(const std::string& str)
{
	Entity entity;
	each<Tag>([&](const Entity& e, const Tag& tag) {
		if(tag.str == str)
		{
			entity = e;
			return;
		}
	});
	return entity;
}

[[nodiscard]] size_t Registry::getSize() const
{
	return entities.size() - freeIds.size();
}

void Registry::all(std::function<void(const Entity&)> func)
{
	for(id_type i = 0; i < entities.size(); i++)
		func(Entity(i, entities[i].version, *this));
}

[[nodiscard]] bool Registry::valid(const Entity& e) const
{
	return e.id() < entities.size() && e.version() == entities[e.id()].version;
}

void Registry::update(Time dt)
{
	for(auto& system : systems)
		system->update(dt, *this);
}

void Registry::addSystem(System* system)
{
	systems.push_back(system);
	system->init();
}

void Registry::removeSystem(System* system)
{
	system->deinit();
	systems.erase(std::remove(systems.begin(), systems.end(), system));
}

void Registry::enableSystem(System* system)
{
	const auto it = std::ranges::find(disabledSystems, system);
	assert(it != disabledSystems.end());
	disabledSystems.erase(it);
	systems.push_back(system);
}

void Registry::disableSystem(System* system)
{
	const auto it = std::ranges::find(systems, system);
	assert(it != systems.end());
	systems.erase(it);
	disabledSystems.push_back(system);
}

[[nodiscard]] id_type Registry::requestId()
{
	id_type id;
	if(freeIds.empty())
	{
		id = static_cast<id_type>(entities.size());
		entities.emplace_back();
	}
	else
	{
		id = freeIds.back();
		freeIds.pop_back();
	}
	return id;
}

void Registry::recycleId(id_type id)
{
	if(id < entities.size())
		freeIds.push_back(id);
}

} // namespace clem