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

void Rigidbody::setMass(float m)
{
	assert(m > 0);
	mass = m;
}
} // namespace clem