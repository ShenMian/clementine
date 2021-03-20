﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Component/Tag.h"
#include "Clem/Core/Application.h"
#include "Clem/Profiler.h"
#include "Clem/Renderer/Renderer.h"
#include "Entity.h"

#include "Clem/Physics/Rigidbody.h"
#include "Clem/Renderer/Sprite.h"

Entity Scene::createEntity()
{
	return getEntityById(registry.create());
}

Entity Scene::createEntity(const std::string& tag)
{
	auto& e = getEntityById(registry.create());
	e.addComponent<Tag>(tag);
	return e;
}

Entity Scene::getEntityById(entity_id id)
{
	if(registry.valid(id))
		return {id, this};
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

void Scene::destoryEntity(entity_id id)
{
	registry.destroy(id);
}

void Scene::update(float dt)
{
	PROFILE_FUNC();

	auto view = registry.view<Rigidbody>();
	for(auto i : view)
	{
		auto& entity = getEntityById(i);
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
		auto& entity = getEntityById(i);
		auto& sprite = entity.getComponent<Sprite>();
		buf.drawSprite({0, 0}, sprite);
	}

	renderer.swapBuffers();
	renderer.render();
}
