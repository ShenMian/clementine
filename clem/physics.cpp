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
			isCollide(entitys[i]->getPhysicsBody(), entitys[j]->getPhysicsBody());

		entitys[i]->position += entitys[i]->velocity;
	}
}

bool Physics::isCollide(Entity* a, Entity* b)
{
	return isCollide(a->getPhysicsBody(), b->getPhysicsBody());
}

bool Physics::isCollide(const Rect& a, const Rect& b) const
{
	if(((a.x <= b.x && b.x <= a.right()) || (a.x <= b.right() && b.right() <= a.right())) && ((a.bottom() <= b.y && b.y <= a.y) || (a.x <= b.bottom() && b.bottom() <= a.y)))
		return true;
	else
		return false;
}

bool Physics::isCollide(const Point& p, const Rect& r) const
{
	if(r.x <= p.x && p.x <= r.right() && r.bottom() <= p.y && p.y <= r.y)
		return true;
	else
		return false;
}

