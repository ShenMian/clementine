// Copyright 2021 SMS
// License(Apache-2.0)

#include "Scene.h"
#include "Clem/Core/Application.h"
#include "Clem/Profiler.h"
#include "Clem/Renderer/Renderer.h"
#include "Clem/Window.h"
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
	PROFILE_FUNC();
}

void Scene::render(float dt)
{
	PROFILE_FUNC();

	auto& renderer = Renderer::getInstance();
	auto& buf      = renderer.getBuffer();
	// buf.clear();

	auto view = registry.view<Sprite>();
	for(auto i : view)
	{
		Entity e(i, this);
		auto&  s = e.getComponent<Sprite>();
		buf.drawSprite({0, 0}, s);
	}

	renderer.swapBuffers();
	renderer.render();

	auto& app = Application::getInstance();
	Window::setTitle(app.getName() + " | " + std::to_string(app.getFramesPerSecond()) + "FPS");
}
