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

void Factor::update(long dt)
{
	for(auto c : components)
		c->update();

	position += velocity * (dt / 1000);
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

void Factor::setVelocity(const Vec2& v)
{
	velocity = v;
}

Texture& Factor::getTexture()
{
	return texture;
}
