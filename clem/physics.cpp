// Copyright 2020 SMS
// License(Apache-2.0)
// 物理引擎

#include "physics.h"
#include "entity.h"

using std::vector;

void Physics::update(vector<Entity*>& entitys) const
{
	for(ushort i = 0; i < entitys.size() - 1; i ++)
	{
		entitys[i]->velocity += entitys[i]->accelerate;

		for(ushort j = i + 1; j < entitys.size(); j++)
			isCollide(entitys[i]->getHitbox(), entitys[j]->getHitbox());

		entitys[i]->setPosition(entitys[i]->getPosition() + entitys[i]->velocity);
	}
}

bool Physics::isCollide(const Entity* a, const Entity* b) const
{
	return false;
}

bool Physics::isCollide(const Rect& a, const Rect& b) const
{
	return false;
}

