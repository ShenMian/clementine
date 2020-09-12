// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "entity.h"
#include "scene.h"
#include "component.h"
#include <algorithm>
#include <assert.h>

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
	auto it = std::find(components.begin(), components.end(), com);
	if(it != components.end())
		components.erase(it);
	else
		assert(false);
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
