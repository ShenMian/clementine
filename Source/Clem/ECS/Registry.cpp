// Copyright 2021 SMS
// License(Apache-2.0)

#include "Registry.h"
#include "Archtype.h"
#include "Chunk.h"
#include "System.h"
#include <algorithm>

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
	freeId.push_back(id);
	if(id < entities.size())
		freeId.push_back(id);
	// freeId.erase(std::remove_if(freeId.begin(), freeId.end(), [this](auto id) { return id < entities.size(); }), freeId.end());
}

size_t Registry::getSize() const
{
	if(entities.size() > freeId.size())
		return entities.size() - freeId.size();
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

Chunk& Registry::getChunk(const Entity& e) const
{
	return *entities[e.id].chunk;
}

id_type Registry::getNewId()
{
	id_type id;
	if(freeId.empty())
	{
		id = static_cast<id_type>(entities.size());
		entities.emplace_back();
	}
	else
	{
		id = freeId.back();
		freeId.pop_back();
	}
	return id;
}
} // namespace clem