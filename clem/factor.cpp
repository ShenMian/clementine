// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "factor.h"
#include "scene.h"
#include "component.h"
#include <algorithm>
#include <cassert>

Factor::Factor()
		: scene(nullptr)
{
}

Factor::Factor(Scene& s)
{
	s.addFactor(*this);
}

Factor::Factor(const Size& s)
		: texture(s), scene(nullptr)
{
}

Factor::Factor(const Texture& t)
		: texture(t), scene(nullptr)
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
	com.setOwner(this);
	com.onAdd();
	components.push_back(&com);
}

void Factor::removeComponent(Component& com)
{
	auto it = std::find(components.begin(), components.end(), &com);
	if(it != components.end())
	{
		(*it)->onRemove();
		(*it)->setOwner(nullptr);
		components.erase(it);
	}
	else
		assert(false);
}

void Factor::setScene(Scene* s)
{
	scene = s;
}

Scene* Factor::getScene() const
{
	return scene;
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
