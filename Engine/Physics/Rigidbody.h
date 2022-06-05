// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <Math/Math.hpp>

namespace phys
{

class Rigidbody
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
	float angularVelocity = 0.f;

	float linearDamping = 0.f;
	float angularDamping = 0.f;

	bool awake = true;

	float gravityScale = 0.f;

	Vector3 force;
	float torque = 0.f;

	void mass(float m);
	float mass() const;
	float invMass() const;

	void inertia(float i);
	float inertia() const;
	float invInertia() const;

private:
	float mass_ = 1.f, invMass_ = mass_ / 1.f;
	float inertia_ = 1.f, invInertia_ = inertia_ / 1.f;
};

struct Material
{
	float staticFriction;
	float dynamicFriction;
	float restitution;
};

}
