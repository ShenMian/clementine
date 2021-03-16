// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Scene.h"
#include "clem/log.h"

NEntity::NEntity(entt::entity id, NScene* scene)
		: id(id), scene(scene)
{
}

entt::entity NEntity::getId() const
{
	return id;
}

NScene* NEntity::getScene() const
{
	return scene;
}
