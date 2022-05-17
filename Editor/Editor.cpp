// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Editor.h"
#include <Input/KeyTrigger.h>
#include <Input/ChordTrigger.h>
#include <Audio/Sound.h>
#include <Audio/Source.h>
#include <Audio/Listener.h>
#include <Audio/Device.h>
#include <thread>

#include <Event/Emitter.hpp>

#include <Physics/Algorithm.hpp>
#include <Physics/Rigidbody.h>

#include <ECS/Archetype.hpp>
#include <ECS/Entity.hpp>
#include <ECS/Registry.h>
#include <ECS/View.hpp>

using std::chrono::microseconds;
using namespace input;

struct PositionComponent
{
	DECLARE_TYPE

	Vector3 position;
};

struct RotationComponent
{
	DECLARE_TYPE

	Quaternion rotation;
};

struct ScaleComponent
{
	DECLARE_TYPE

	Vector3 scale;
};

Editor::Editor()
	: window("Editor", {1920 / 2, 1080 / 2})
{
	Renderer::init(window);
	UI::init(window);
	Input::setWindow(window);

	window.onClose = [this]() { this->requestExit(); };

	actionMap.add(std::make_shared<KeyTrigger>(Key::Escape), [this]() { this->requestExit(); });

	window.setVisible(true);

	ecs::Registry registry;
	auto entity = registry.create();
	registry.destroy(entity);

	ecs::Iterator<PositionComponent, RotationComponent> it;
	// const auto& [pos, rot] = *it;
}

Editor::~Editor()
{
	UI::deinit();
	Renderer::deinit();
}

struct Contact
{
	Vector3 points[2];
	int pointCount = 0;
};

void Editor::loop()
{
	auto prev = std::chrono::high_resolution_clock::now();
	while(!exitRequested)
	{
		const auto curr = std::chrono::high_resolution_clock::now();
		const auto dt = std::chrono::duration_cast<microseconds>(curr - prev);
		prev = curr;

		// const auto& view = register.get<TransformComponent, RigidbodyComponent>();
		// for(auto& [trans, body] : view) { ... };
		{
			float dt;
			Transform trans;
			phys::Rigidbody body;
			body.linearVelocity += dt * body.force * body.invMass();
			body.angularVelocity += dt * body.torque * body.invInertia();
			body.force = Vector3::zero;
			body.torque = 0.f;

			trans.position() += dt * body.linearVelocity;
		}

		std::vector<phys::Collider*> colliders;
		if(!colliders.empty())
		{
			for(size_t i = 0; i < colliders.size() - 1; i++)
			{
				for(size_t j = i + 1; colliders.size(); j++)
					if(colliders[i]->intersects(*colliders[j]))
						;
			}
		}

		update(dt);
		render();
	}
}

void Editor::requestExit()
{
	exitRequested = true;
}

void Editor::update(microseconds dt)
{
	actionMap.update();
	window.update();
}

void Editor::render()
{
	renderUI();
}

void Editor::renderUI()
{
	UI::beginFrame();

	UI::endFrame();
}

void Editor::init()
{
	Renderer::setAPI(Renderer::API::OpenGL);

	audio::Device::init();
	Window::init();
}

void Editor::deinit()
{
	Window::deinit();
	audio::Device::deinit();
}
