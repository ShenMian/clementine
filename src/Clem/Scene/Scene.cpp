// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Core/Application.h"
#include "Clem/Profiler.h"
#include "Clem/Renderer/Renderer.h"
#include "Entity.h"

#include "Clem/Component/Script.h"
#include "Clem/Component/Tag.h"
#include "Clem/Component/Transform.h"
#include "Clem/Physics/Collider.h"
#include "Clem/Physics/Rigidbody.h"
#include "Clem/Renderer/Sprite.h"
#include "Clem/Ui/Text.h"

Entity Scene::createEntity()
{
	auto e = getEntityById(registry.create());
	e.addComponent<Transform>();
	return e;
}

Entity Scene::createEntity(const std::string& tag)
{
	auto e = createEntity();
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
		auto e = getEntityById(i);
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

	auto scriptView = registry.view<Transform, Script>();
	for(auto [entity, transform, script] : scriptView.each())
		script.onUpdate(dt);

	auto bodyView = registry.view<Transform, Rigidbody>();
	for(auto [entity, transform, body] : bodyView.each())
	{
		transform.position += body.velocity;
		body.velocity += body.acceleration * dt;
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

#include "Clem/Core/Math/Rect.h"

void Scene::render(float dt)
{
	PROFILE_FUNC();

	static auto& renderer = Renderer::getInstance();
	auto&        buf      = renderer.getBuffer();
	buf.clear();

	// Render sprites
	auto spriteView = registry.view<Transform, Sprite>();
	for(auto [entity, transform, sprite] : spriteView.each())
		buf.drawSprite(transform.position, sprite);

	// Render UI
	auto textView = registry.view<Transform, Text>();
	for(auto [entity, transform, text] : textView.each())
		buf.drawString(transform.position, text.text);

	renderer.swapBuffers();
	renderer.output();
}
