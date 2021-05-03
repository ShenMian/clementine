// Copyright 2021 SMS
// License(Apache-2.0)
// 碰撞体

#include "Collider.h"
#include "Rigidbody.h"
#include <cassert>

namespace clem
{
Point2 Collider::getPosition() const
{
	return rigidbody->getPosition() + offset;
}

void Collider::setOffset(Point2 o)
{
	offset = o;
}

Point2 Collider::getOffset() const
{
	return offset;
}

void Collider::setRigidbody(Rigidbody* rb)
{
	rigidbody = rb;
}

Rigidbody* Collider::getRigidbody() const
{
	return rigidbody;
}
} // namespace clem