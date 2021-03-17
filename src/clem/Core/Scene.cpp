// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Entity.h"

NEntity NScene::createEntity()
{
	return NEntity(registry.create(), this);
}

void NScene::destoryEntity(NEntity e)
{
	registry.destroy(e.getId());
}

void NScene::update(long dt)
{
}

void NScene::render(long dt)
{
	// auto view = registry.view<>();
}
