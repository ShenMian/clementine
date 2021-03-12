// Copyright 2020 SMS
// License(Apache-2.0)
// ¸ÕÌå

#include "rigidbody.h"
#include "collider.h"

using std::vector;

void Rigidbody::update(float dt)
{
	auto pos = owner->getPosition();
	velocity += accelerate * dt;
	pos += velocity * dt;
	owner->setPosition(pos);
}

void Rigidbody::addCollider(Collider& c)
{
	c.setOwner(this);
	colliders.push_back(&c);
}

const vector<Collider*>& Rigidbody::getColliders() const
{
	return colliders;
}

void Rigidbody::onAdd()
{
	owner->getScene()->addRigidbody(*this);
}

void Rigidbody::onRemove()
{
	owner->getScene()->removeRigidbody(*this);
}
