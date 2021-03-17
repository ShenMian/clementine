// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Scene.h"
#include "clem/log.h"

Entity::Entity(entt::entity id, Scene* scene)
		: id(id), scene(scene)
{
}

entt::entity Entity::getId() const
{
	return id;
}

Scene* Entity::getScene() const
{
	return scene;
}
