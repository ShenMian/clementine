// Copyright 2021 SMS
// License(Apache-2.0)

#include "Registry.h"
#include "Archtype.h"
#include "Chunk.h"
#include <algorithm>

namespace clem
{
struct EntityInfo
{
	Archtype<>* archtype = nullptr;
	Chunk*      chunk    = nullptr;
	size_t      version  = 0;
};

AEntity Registry::create()
{
	const auto id = getNewId();
	return AEntity(id, entities[id].version, *this);
}

void Registry::destory(const AEntity& e)
{
	const auto id = e.getId();
	entities[id].version++;
	if(id < entities.size())
		freeId.push_back(id);
}

size_t Registry::getSize() const
{
	if(entities.size() > freeId.size())
		return entities.size() - freeId.size();
	else
		return 0;
}

bool Registry::isValid(const AEntity& e) const
{
	return e.getId() < entities.size() && e.getVersion() == entities[e.getId()].version;
}

const Archtype<>& Registry::getArchtype(const Archtype<>& at)
{
	auto pair = archtypes.insert(at);
	return *(pair.first);
}

EntityId Registry::getNewId()
{
	EntityId id;
	if(freeId.empty())
	{
		id = static_cast<EntityId>(entities.size());
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