// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Scene.h"
#include "clem/log.h"

Entity::Entity(entity_id id, Scene* scene)
		: id(id), scene(scene)
{
}

entity_id Entity::getId() const
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

Entity::operator entity_id() const
{
	return id;
}
