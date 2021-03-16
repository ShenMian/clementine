// Copyright 2021 SMS
// License(Apache-2.0)
// 圆形碰撞体

#include "circle_collider.h"
#include "box_collider.h"
#include "clem/Profiler.h"
#include <cassert>

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(float radius)
		: radius(radius)
{
}

bool CircleCollider::collides(const Collider& other) const
{
	PROFILE_FUNC();

	if(auto o = dynamic_cast<const CircleCollider*>(&other))
		return getPosition().distance(o->getPosition()) <= getRadius() + o->getRadius();
	else if(auto o = dynamic_cast<const BoxCollider*>(&other))
		return o->collides(*this);
	else
		assert(false);
}

/**
 * @brief 设置半径
 * 
 * @param r 半径
 */
void CircleCollider::setRadius(float r)
{
	radius = r;
}

/**
 * @brief 获取半径
 * 
 * @return float 半径
 */
float CircleCollider::getRadius() const
{
	return radius;
}
