// Copyright 2021 SMS
// License(Apache-2.0)

#include "PhysicsWorld.h"
#include "Clem/Components/Transform.h"
#include "Clem/Profiler.h"
#include "Clem/Scene/Scene.h"
#include "Rigidbody.h"

namespace clem
{

PhysicsWorld::PhysicsWorld(Scene& s)
		: scene(s)
{
}

void PhysicsWorld::update(float dt)
{
	PROFILE_FUNC();

	auto view = scene.registry.view<Transform, Rigidbody>();
	for(auto [e, t, body] : view.each())
	{
		switch(body.getType())
		{
		case Rigidbody::Type::Dynamic:
			body.velocity += (body.getAcceleration() + gravity) * dt; // v += (a + g) * dt;
			break;

		case Rigidbody::Type::Kinematic:
			body.velocity += body.getAcceleration() * dt; // v += a * dt;
			break;

		case Rigidbody::Type::Static:
			continue;
		}
		t.setPosition(t.getPosition() + body.velocity); // p += v * dt;
	}
}

void PhysicsWorld::setGravity(const Vector2& g)
{
	gravity = g;
}

} // namespace clem
