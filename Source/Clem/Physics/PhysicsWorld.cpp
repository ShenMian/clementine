// Copyright 2021 SMS
// License(Apache-2.0)

#include "PhysicsWorld.h"
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

	for(auto body : bodies)
	{
		switch(body->getType())
		{
		case Rigidbody::Type::Dynamic:
			body->velocity += (body->getAcceleration() + gravity) * dt; // v += (a + g) * dt;
			break;

		case Rigidbody::Type::Kinematic:
			body->velocity += body->getAcceleration() * dt; // v += a * dt;
			break;

		case Rigidbody::Type::Static:
			continue;
		}
		body->setPosition(body->getPosition() + body->velocity); // p += v * dt;
	}

	/*
	auto view = scene.registry.view<Rigidbody>();
	for(auto [e, body] : view.each())
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
		body.setPosition(body.getPosition() + body.velocity); // p += v * dt;
	}*/
}

void PhysicsWorld::addBody(Rigidbody& b)
{
	bodies.push_back(&b);
}

bool PhysicsWorld::removeBody(Rigidbody& b)
{
	auto it = std::find(bodies.begin(), bodies.end(), &b);
	if(it == bodies.end())
		return false;
	bodies.erase(it);
	return true;
}

void PhysicsWorld::setGravity(const Vector2& g)
{
	gravity = g;
}

} // namespace clem
