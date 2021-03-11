// Copyright 2020 SMS
// License(Apache-2.0)
// ¸ÕÌå

#include "rigidbody.h"

void Rigidbody::onAdd()
{
	owner->getScene()->addRigidbody(*this);
}

void Rigidbody::onRemove()
{
	owner->getScene()->removeRigidbody(*this);
}

void Rigidbody::addCollider(Collider& c)
{
	colliders.push_back(&c);
}
