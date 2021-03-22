// Copyright 2021 SMS
// License(Apache-2.0)
// 圆形碰撞体

#include "CircleCollider.h"
#include <cassert>

CircleCollider::CircleCollider(float r)
		: radius(r)
{
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
