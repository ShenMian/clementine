// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "factor.h"
#include "scene.h"
#include "component.h"
#include "physics/collider.h"
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

void Factor::update(float dt)
{
	for(auto c : components)
		c->update(dt);
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

const Point& Factor::getPosition() const
{
	return position;
}

void Factor::onCollision(Collider, Collider)
{
}
