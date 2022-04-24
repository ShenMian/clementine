// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Rigidbody.h"
#include <numeric>

namespace phys
{

void Rigidbody::mass(float m)
{
	assert(mass_ > std::numeric_limits<float>::epsilon());
	mass_ = m;
	invMass_ = 1.f / mass_;
}

float Rigidbody::mass() const
{
	return mass_;
}

float Rigidbody::invMass() const
{
	return invMass_;
}

void Rigidbody::inertia(float i)
{
	inertia_ = i;
	invInertia_ = 1.f / inertia_;
}

float Rigidbody::inertia() const
{
	return inertia_;
}

float Rigidbody::invInertia() const
{
	return invInertia_;
}

}
