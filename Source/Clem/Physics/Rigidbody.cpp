// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rigidbody.h"
#include <cassert>

namespace clem
{
void Rigidbody::addForce(const Vector2& f)
{
	acceleration += f / mass;
}

void Rigidbody::setAcceleration(const Vector2& acc)
{
	acceleration = acc;
}

const Vector2& Rigidbody::getAcceleration() const
{
	return acceleration;
}

void Rigidbody::setMass(float m)
{
	assert(m >= 0);
	mass = m;
}

void Rigidbody::setEntity(const Entity& e)
{
	entity = e;
}

const Entity& Rigidbody::getEntity() const
{
	return entity;
}
} // namespace clem