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
		auto pos = t.getLocalPosition();
		body.velocity += body.getAcceleration() * dt;
		t.setLocalPosition(pos += body.velocity);
	}
}

} // namespace clem
