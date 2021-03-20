// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Core/Application.h"
#include "Clem/Profiler.h"
#include "Clem/Renderer/Renderer.h"
#include "Entity.h"

#include "Clem/Physics/Rigidbody.h"
#include "Clem/Renderer/Sprite.h"

Entity Scene::createEntity()
{
	return getEntity(registry.create());
}

Entity Scene::getEntity(entity_id id)
{
	return {id, this};
}

void Scene::destoryEntity(Entity e)
{
	registry.destroy(e.getId());
}

void Scene::update(float dt)
{
	PROFILE_FUNC();

	auto view = registry.view<Rigidbody>();
	for(auto i : view)
	{
		auto& entity = getEntity(i);
		auto& body   = entity.getComponent<Rigidbody>();
		body.velocity += body.acceleration * dt;
	}
}

void Scene::render(float dt)
{
	PROFILE_FUNC();

	static auto& renderer = Renderer::getInstance();
	auto&        buf      = renderer.getBuffer();
	buf.clear();

	auto view = registry.view<Sprite>();
	for(auto i : view)
	{
		auto& entity = getEntity(i);
		auto& sprite = entity.getComponent<Sprite>();
		buf.drawSprite({0, 0}, sprite);
	}

	renderer.swapBuffers();
	renderer.render();
}
