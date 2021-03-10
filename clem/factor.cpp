// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "factor.h"
#include "scene.h"
#include "component.h"
#include <algorithm>
#include <cassert>

Factor::Factor()
{
}

Factor::Factor(const Size& s)
		: texture(s)
{
}

Factor::Factor(const Texture& t)
		: texture(t)
{
}

void Factor::update(float dt)
{
	for(auto c : components)
		c->update();

	position += velocity * dt;
}

void Factor::addComponent(Component& com)
{
	components.push_back(&com);
}

void Factor::removeComponent(Component& com)
{
	auto it = std::find(components.begin(), components.end(), &com);
	if(it != components.end())
		components.erase(it);
	else
		assert(false);
}

void Factor::setPosition(const Point& p)
{
	this->position = p;
}

void Factor::setTexture(const Texture& t)
{
	this->texture = t;
}

const Point& Factor::getPosition() const
{
	return position;
}

void Factor::setVelocity(const Vec2& v)
{
	velocity = v;
}

Texture& Factor::getTexture()
{
	return texture;
}
