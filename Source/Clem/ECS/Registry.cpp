// Copyright 2021 SMS
// License(Apache-2.0)

#include "Registry.h"
#include "Archtype.h"
#include "Chunk.h"
#include "System.h"
#include <algorithm>
#include <cassert>

namespace clem
{

Entity Registry::create()
{
	const auto id      = getNewId();
	entities[id].chunk = &chunk;
	return Entity(id, entities[id].version, *this);
}

void Registry::destory(const Entity& e)
{
	const auto id = e.id;
	entities[id].version++;
	freeIds.push_back(id);
	if(id < entities.size())
		freeIds.push_back(id);
	// freeIds.erase(std::remove_if(freeIds.begin(), freeIds.end(), [this](auto id) { return id < entities.size(); }), freeIds.end());
}

size_t Registry::getSize() const
{
	if(entities.size() > freeIds.size())
		return entities.size() - freeIds.size();
	else
		return 0;
}

bool Registry::isValid(const Entity& e) const
{
	return e.id < entities.size() && e.version == entities[e.id].version;
}

void Registry::update(float dt)
{
	for(auto& system : systems)
		system->update(dt);
}

void Registry::addSystem(System& s)
{
	systems.push_back(&s);
	s.init();
}

void Registry::removeSystem(System& s)
{
	s.deinit();
	systems.erase(std::remove(systems.begin(), systems.end(), &s));
}

void Registry::enableSystem(System& system)
{
	const auto it = std::find(disabledSystems.begin(), disabledSystems.end(), &system);
	assert(it != disabledSystems.end());
	disabledSystems.erase(it);
	systems.push_back(&system);
}

void Registry::disableSystem(System& system)
{
	const auto it = std::find(systems.begin(), systems.end(), &system);
	assert(it != systems.end());
	systems.erase(it);
	disabledSystems.push_back(&system);
}

Chunk& Registry::getChunk(const Entity& e) const
{
	return *entities[e.id].chunk;
}

id_type Registry::getNewId()
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

} // namespace clem