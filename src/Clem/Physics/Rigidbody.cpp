// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rigidbody.h"

void Rigidbody::addForce(const Vector2& f)
{
	acceleration += f / mass;
}