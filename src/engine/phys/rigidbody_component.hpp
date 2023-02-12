// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "ecs/component.hpp"
#include <math/math.hpp>

namespace phys
{

class Rigidbody : public ecs::Component
{
public:
	enum class Type
	{
		Static,
		Kinematic,
		Dynamic
	};

	Type type = Type::Static;

	Vector3 linearVelocity;
	float   angularVelocity = 0.f;

	Vector3 force;
	float   torque = 0.f;

	float mass = 1.f;
};

} // namespace phys
