// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Components/Components.h"
#include "Clem/Log.h"
#include "Clem/Profiler.h"
#include "Clem/Rendering/Rendering.h"
#include "Entity.h"

#include "Clem/Physics/Rigidbody.h"

using std::string;
using std::string_view;

namespace clem
{
Entity Scene::createEntity(const string& tag)
{
	auto e = Entity(registry.create(), this);
	e.addComponent<Transform>();
	e.addComponent<Tag>(tag);
	return e;
}

Entity Scene::getEntity(const string_view& tag)
{
	auto view = registry.view<Tag>();
	for(auto [e, t] : view.each())
		if(t.string == tag)
			return Entity(e, this);
	CLEM_CORE_ERROR("get entity with invalid a tag");
	return Entity();
}

void Scene::destroyEntity(const string_view& tag)
{
	registry.destroy(getEntity(tag).getId());
}

void Scene::update(float dt)
{
	PROFILE_FUNC();

	updateScripts(dt);
	updateRigidbodies(dt);
}

void Scene::render(float dt)
{
	PROFILE_FUNC();

	static auto& output = Output::get();
	output.getBuffer().clear();

	renderSprites();

	output.swapBuffers();
	output.update();
}

void Scene::updateScripts(float dt)
{
	auto view = registry.view<Transform, Script>();
	for(auto [e, t, script] : view.each())
		script.onUpdate(dt);
}

void Scene::updateRigidbodies(float dt)
{
	auto view = registry.view<Transform, Rigidbody>();
	for(auto [e, t, body] : view.each())
	{
		auto pos = t.getLocalPosition();
		t.setLocalPosition(pos += body.velocity);
		// body.velocity += body.acceleration * dt;
	}
}

void Scene::renderSprites()
{
	PROFILE_FUNC();

	auto& buf  = Output::get().getBuffer();
	auto  view = registry.view<Transform, const Sprite>();
	for(auto [e, t, sprite] : view.each())
		buf.drawSprite(t.getPosition(), sprite);
}
} // namespace clem

/*
	const size_t size = 10;
	for(int i = 0; i < size - 1; i++)
		for(int j = i + 1; j < size; j++)
			handle(colliders[i], colliders[j]);

	std::vector<int> v;
	for(auto i = v.begin(); i < v.end() - 1; i++)
		;

	auto view = registry.view<Rigidbody, Collider>();
	for(auto i = view.begin(); i != view.end() - 1; ++i)
		for(auto j = i + 1; j != view.end(); ++j)
			handle(*i, *j);

	for(auto [entity, body, collider] : colliderView.each())
	{
	}

	getPosition().distance(o->getPosition()) <= getRadius() + o->getRadius();
	return getRect().contains(o->getRect());
	*/