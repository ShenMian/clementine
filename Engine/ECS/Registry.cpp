// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Registry.h"
#include <cassert>

namespace ecs
{

Entity Registry::create()
{
	return entities_[request()];
}

void Registry::destroy(const Entity& entity)
{
	recycle(entity.id());
}

bool Registry::valid(const Entity& entity) const noexcept
{
	return entity.id() < entities_.size() && entity == entities_[entity.id()];
}

Entity::id_type Registry::request()
{
	if(freeIds_.empty())
	{
		const auto id = entities_.size();
		entities_.emplace_back(static_cast<Entity::id_type>(id), 0, *this);
		return id;
	}
	const auto id = freeIds_.back();
	freeIds_.pop_back();
	return id;
}

void Registry::recycle(Entity::id_type id)
{
	freeIds_.push_back(id);
	entities_[id].version_++;
}

}
