// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Core/Application.h"
#include "Clem/Log.h"
#include "Clem/Profiler.h"
#include "Clem/Renderer/Output.h"
#include "Entity.h"

#include "Clem/Component/Script.h"
#include "Clem/Component/Tag.h"
#include "Clem/Component/Transform.h"
#include "Clem/Physics/Collider.h"
#include "Clem/Physics/Rigidbody.h"
#include "Clem/Renderer/Sprite.h"
#include "Clem/Ui/Text.h"

using std::string;

Entity Scene::createEntity(const string& tag)
{
	auto e = Entity(registry.create(), this);
	e.addComponent<Transform>();
	e.addComponent<Tag>(tag);
	return e;
}

Entity Scene::getEntityByTag(const string& tag_)
{
	auto view = registry.view<Tag>();
	for(auto [id, tag] : view.each())
		if(tag.tag == tag_)
			return Entity(id, this);
	CLEM_CORE_ERROR("get entity with invalid a tag");
	return Entity();
}

void Scene::removeEntity(Entity e)
{
	registry.destroy(e.getId());
	// registry.remove(id);
}

void Scene::update(float dt)
{
	PROFILE_FUNC();

	auto scriptView = registry.view<Transform, Script>();
	for(auto [e, t, script] : scriptView.each())
		script.onUpdate(dt);

	auto bodyView = registry.view<Transform, Rigidbody>();
	for(auto [e, t, body] : bodyView.each())
	{
		auto pos = t.getLocalPosition();
		t.setLocalPosition(pos += body.velocity);
		// body.velocity += body.acceleration * dt;
	}

	//const size_t size = 10;
	//for(int i = 0; i < size - 1; i++)
	//	for(int j = i + 1; j < size; j++)
	//		handle(colliders[i], colliders[j]);

	//std::vector<int> v;
	//for(auto i = v.begin(); i < v.end() - 1; i++)
	//	;

	//auto view = registry.view<Rigidbody, Collider>();
	//for(auto i = view.begin(); i != view.end() - 1; ++i)
	//	for(auto j = i + 1; j != view.end(); ++j)
	//		handle(*i, *j);

	//for(auto [entity, body, collider] : colliderView.each())
	//{
	//}

	// getPosition().distance(o->getPosition()) <= getRadius() + o->getRadius();
	// return getRect().contains(o->getRect());
}

#include "Clem/Core/Math/Rect2.h"

void Scene::render(float dt)
{
	PROFILE_FUNC();

	static auto& output = Output::get();
	output.getBuffer().clear();

	renderSprites();

	output.swapBuffers();
	output.update();
}

void Scene::renderSprites()
{
	PROFILE_FUNC();

	auto& buf  = Output::get().getBuffer();
	auto  view = registry.view<Transform, const Sprite>();
	for(auto [e, t, sprite] : view.each())
		buf.drawSprite(t.getPosition(), sprite);
}
