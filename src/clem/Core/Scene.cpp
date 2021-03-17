// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Entity.h"
#include "Sprite.h"

Entity NScene::createEntity()
{
	return Entity(registry.create(), this);
}

void NScene::destoryEntity(Entity e)
{
	registry.destroy(e.getId());
}

void NScene::update(long dt)
{
}

void NScene::render(long dt)
{
	auto view = registry.view<NSprite>();
	for(auto i : view)
	{
		Entity e(i, this);
		auto& s = e.getComponent<NSprite>();
	}
}