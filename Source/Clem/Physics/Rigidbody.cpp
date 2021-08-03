// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rigidbody.h"
#include "Components/Transform.h"
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

void Rigidbody::setAcceleration(const Vector2& acc)
{
	force = acc * mass;
}

Vector2 Rigidbody::getAcceleration() const
{
	return force / mass;
}

} // namespace clem