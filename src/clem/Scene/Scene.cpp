// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Core/Application.h"
#include "Clem/Profiler.h"
#include "Clem/Renderer/Renderer.h"
#include "Entity.h"

#include "Clem/Component/Tag.h"
#include "Clem/Component/Transform.h"
#include "Clem/Physics/Rigidbody.h"
#include "Clem/Renderer/Sprite.h"

Entity Scene::createEntity()
{
	auto& e = getEntityById(registry.create());
	e.addComponent<Transform>();
	return e;
}

Entity Scene::createEntity(const std::string& tag)
{
	auto& e = createEntity();
	e.addComponent<Tag>(tag);
	return e;
}

Entity Scene::getEntityById(entity_id id)
{
	if(registry.valid(id))
		return Entity(id, this);
	else
		return Entity();
}

Entity Scene::getEntityByTag(const std::string& tag)
{
	auto view = registry.view<Tag>();
	for(auto i : view)
	{
		auto& e = getEntityById(i);
		if(e.getComponent<Tag>().tag == tag)
			return e;
	}
	return Entity();
}

void Scene::removeEntity(entity_id id)
{
	registry.destroy(id);
	// registry.remove(id);
}

void Scene::update(float dt)
{
	PROFILE_FUNC();

	auto view = registry.view<Transform, Rigidbody>();
	for(auto [entity, transform, body] : view.each())
	{
		transform.position += body.velocity;
		body.velocity      += body.acceleration * dt;
	}
}

void Scene::render(float dt)
{
	PROFILE_FUNC();

	static auto& renderer = Renderer::getInstance();
	auto&        buf      = renderer.getBuffer();
	buf.clear();

	auto view = registry.view<Transform, Sprite>();
	for(auto [entity, transform, sprite] : view.each())
	{
		buf.drawSprite(transform.position, sprite);
	}

	renderer.swapBuffers();
	renderer.render();
}
