// Copyright 2020 SMS
// License(Apache-2.0)
// 简易物理引擎

#include "simple_physics.h"
#include "entity.h"

void SimplePhysics::update(Entity& e)
{
	e.setVelocity(e.getVelocity() + e.getAccelerate());
	auto nextPos = e.getPosition() + e.getVelocity();

	for(auto rect : border)
	{
		if(rect.bottom() <= nextPos.y && nextPos.y <= rect.y)
		{
			auto xDis = rect.x - nextPos.x;
			if((xDis < 0 && rect.x < nextPos.x) ||
				 (xDis > 0 && nextPos.x < rect.x))
				nextPos.x += xDis;
		}
		if(rect.x <= nextPos.x && nextPos.x <= rect.right())
		{
			auto xDis = rect.y - nextPos.y;
			if((xDis < 0 && rect.y < nextPos.y) ||
				 (xDis > 0 && nextPos.y < rect.y))
				nextPos.y += xDis;
		}
	}

	e.setPosition(nextPos);
}

void SimplePhysics::addBorder(const Rect& rect)
{
	border.push_back(rect);
}
