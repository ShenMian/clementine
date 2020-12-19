// Copyright 2020 SMS
// License(Apache-2.0)
// ΚµΜε

#include "entity.h"

void Entity::setVelocity(const Vec2& v)
{
	velocity = v;
}

const Vec2& Entity::getVelocity() const
{
	return velocity;
}

void Entity::setAccelerate(const Vec2& a)
{
	accelerate = a;
}

const Vec2& Entity::getAccelerate() const
{
	return accelerate;
}

void Entity::setPhysicsBody(const Rect& body)
{
	physicsBody = body;
}

const Rect& Entity::getPhysicsBody()
{
	physicsBody.x = position.x;
	physicsBody.y = position.y;
	return physicsBody;
}
