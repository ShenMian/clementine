// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Scene.h"
#include "clem/log.h"

Entity::Entity(entt::entity id, NScene* scene)
		: id(id), scene(scene)
{
}

entt::entity Entity::getId() const
{
	return id;
}

NScene* Entity::getScene() const
{
	return scene;
}
