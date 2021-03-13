// Copyright 2020 SMS
// License(Apache-2.0)
// 圆形碰撞体

#include "circle_collider.h"
#include "box_collider.h"
#include <cassert>

/**
 * @brief 检测是否与其他碰撞体发生碰撞
 * 
 * @param other 其他碰撞体
 * @return true 发生碰撞
 * @return false 未发生碰撞
 */
bool CircleCollider::collides(const Collider& other) const
{
	if(auto o = dynamic_cast<const CircleCollider*>(&other))
		return getPosition().distance(o->getPosition()) <= getRadius() + o->getRadius();
	else if(auto o = dynamic_cast<const BoxCollider*>(&other))
		o->collides(*this);
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
