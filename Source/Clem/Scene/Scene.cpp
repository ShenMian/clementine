// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Components/Components.h"
#include "Clem/Logger.h"
#include "Clem/Profiler.h"
#include "Clem/Rendering/Rendering.h"
#include "Entity.h"

using std::string;
using std::string_view;

namespace clem
{
Scene::Scene()
		: physicsWorld(*this)
{
}

Entity Scene::createEntity(const string& tag)
{
	Entity e(registry.create(), this);
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
	CLEM_LOG_WARN("core", "get entity with invalid a tag");
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
	physicsWorld.update(dt);
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
	PROFILE_FUNC();

	auto view = registry.view<Transform, Script>();
	for(auto [e, t, script] : view.each())
		script.onUpdate(dt);
}

void Scene::renderSprites()
{
	PROFILE_FUNC();

	// TODO: 应该当在 sprites 之一的 depth 发生变化时调用
	sortSprites();

	auto& buf  = Output::get().getBuffer();
	auto  view = registry.view<Transform, const Sprite>();
	for(auto [e, t, sprite] : view.each())
		buf.drawSprite(t.getWorldPosition(), sprite);
}

void Scene::sortSprites()
{
	// FIXME: 无效
	registry.sort<Sprite>([](const Sprite& lhs, const Sprite& rhs) {
		return lhs.getDepth() > rhs.getDepth();
	});
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