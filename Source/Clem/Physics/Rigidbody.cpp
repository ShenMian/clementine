// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rigidbody.h"
#include <cassert>

namespace clem
{
void Rigidbody::addForce(const Vector2& f)
{
	force += f;
}

const Vector2& Rigidbody::getForce() const
{
	return force;
}

Vector2 Rigidbody::getAcceleration() const
{
	return force / mass;
}

void Rigidbody::setMass(float m)
{
	assert(m >= 0);
	mass = m;
}

float Rigidbody::getMass() const
{
	return mass;
}

void Rigidbody::setType(Type t)
{
	type = t;
}

Rigidbody::Type Rigidbody::getType() const
{
	return type;
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