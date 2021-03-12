#include "collider.h"
// Copyright 2020 SMS
// License(Apache-2.0)
// Åö×²Ìå

#include "collider.h"
#include "rigidbody.h"

Collider::Collider()
		: owner(nullptr)
{
}

Collider::~Collider()
{
}

Point Collider::getPosition() const
{
	return owner->getOwner()->getPosition() + offset;
}

void Collider::setOffset(Point o)
{
	offset = o;
}

Point Collider::getOffset() const
{
	return offset;
}

void Collider::setOwner(Rigidbody* o)
{
	owner = o;
}

Rigidbody* Collider::getOwner() const
{
	return owner;
}

#include "circle_collider.h"

bool Collider::collides(const CircleCollider& a, const CircleCollider& b)
{
	auto distance = a.getPosition().distance(b.getPosition());
	return distance <= a.getRadius() + b.getRadius();
}
