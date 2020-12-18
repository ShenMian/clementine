// Copyright 2020 SMS
// License(Apache-2.0)
// ΚµΜε

#include "entity.h"

void Entity::setVelocity(const Vector& v)
{
	velocity = v;
}

const Vector& Entity::getVelocity() const
{
	return velocity;
}

void Entity::setAccelerate(const Vector& a)
{
	accelerate = a;
}

const Vector& Entity::getAccelerate() const
{
	return accelerate;
}

void Entity::setHitbox(const Rect& h)
{
	hitbox = h;
}
const Rect& Entity::getHitbox()
{
	hitbox.x = position.x;
	hitbox.y = position.y;
	return hitbox;
}
