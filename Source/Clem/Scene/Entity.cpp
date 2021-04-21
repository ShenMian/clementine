// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Scene.h"

namespace clem
{
Entity::Entity(id_t id, Scene* scene)
		: id(id), scene(scene)
{
}

Entity::id_t Entity::getId() const
{
	return id;
}

Scene* Entity::getScene() const
{
	return scene;
}

Entity::operator bool() const
{
	return id != entt::null;
}

Entity::operator id_t() const
{
	return id;
}

bool Entity::operator==(const Entity& o) const
{
	return id == o.getId();
}

bool Entity::operator!=(const Entity& o) const
{
	return !(*this == o);
}
} // namespace clem