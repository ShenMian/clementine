// Copyright 2020 SMS
// License(Apache-2.0)
// ÓÎÏ·¶ÔÏó

#include "entity.h"
#include "scene.h"
#include "component.h"

Entity::Entity(const Texture& texture)
		: texture(texture)
{
}

void Entity::update()
{
	for(const auto& com : components)
		com->update(*this);
}

void Entity::addComponent(Component* com)
{
	components.push_back(com);
}

void Entity::removeComponent(Component* com)
{
	// TODO
}

void Entity::setPosition(const Point& pos)
{
	this->position = pos;
}

void Entity::setTexture(const Texture& texture)
{
	this->texture = texture;
}

const Point& Entity::getPosition() const
{
	return position;
}

const Texture& Entity::getTexture() const
{
	return texture;
}

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
