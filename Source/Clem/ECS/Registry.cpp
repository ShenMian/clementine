// Copyright 2021 SMS
// License(Apache-2.0)

#include "Registry.h"
#include "Archtype.h"
#include "Chunk.h"

namespace clem
{

struct EntityInfo
{
	Archtype* archtype = nullptr;
	size_t    version  = 0;
};

AEntity Registry::create()
{
	auto id = getNewId();
	return AEntity(id, entities[id].version, *this);
}

void Registry::destory(AEntity& entity)
{
	auto id = entity.getId();
	entities[id].version++;
	freeId.push_back(id);
}

size_t Registry::getSize() const
{
	if(entities.size() > freeId.size())
		return entities.size() - freeId.size();
	else
		return 0;
}

const Archtype& Registry::getArchtype(const Archtype& archtype)
{
	auto pair = archtypes.insert(archtype);
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
