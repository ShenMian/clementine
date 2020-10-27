// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "factor.h"
#include "scene.h"
#include "component.h"
#include <algorithm>
#include <assert.h>

Factor::Factor(const Texture& texture)
		: texture(texture)
{
}

void Factor::update()
{
	/*
	for(const auto& com : components)
		com->update(*this);
	*/
}

void Factor::addComponent(Component* com)
{
	components.push_back(com);
}

void Factor::removeComponent(Component* com)
{
	auto it = std::find(components.begin(), components.end(), com);
	if(it != components.end())
		components.erase(it);
	else
		assert(false);
}

void Factor::setPosition(const Point& pos)
{
	this->position = pos;
}

void Factor::setTexture(const Texture& texture)
{
	this->texture = texture;
}

const Point& Factor::getPosition() const
{
	return position;
}

const Texture& Factor::getTexture() const
{
	return texture;
}

void Factor::setVelocity(const Vector& v)
{
	velocity = v;
}

const Vector& Factor::getVelocity() const
{
	return velocity;
}

void Factor::setAccelerate(const Vector& a)
{
	accelerate = a;
}

const Vector& Factor::getAccelerate() const
{
	return accelerate;
}
