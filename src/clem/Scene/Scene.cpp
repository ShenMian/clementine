// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Entity.h"
#include "Sprite.h"

Entity Scene::createEntity()
{
	return Entity(registry.create(), this);
}

void Scene::destoryEntity(Entity e)
{
	registry.destroy(e.getId());
}

void Scene::update(float dt)
{
}

void Scene::render(float dt)
{
	auto view = registry.view<Sprite>();
	for(auto i : view)
	{
		Entity e(i, this);
		auto& s = e.getComponent<Sprite>();
	}
}
