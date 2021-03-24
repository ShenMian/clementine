// Copyright 2021 SMS
// License(Apache-2.0)
// 碰撞体

#include "Collider.h"
#include "Rigidbody.h"
#include <cassert>

Point<float> Collider::getPosition() const
{
	// assert(owner);
	return Point<float>(); // owner->getOwner()->getPosition() + offset;
}

void Collider::setOffset(Point<float> o)
{
	offset = o;
}

Point<float> Collider::getOffset() const
{
	return offset;
}

/**
 * @brief 设置拥有者
 * 
 * @param o 拥有者
 */
void Collider::setOwner(Rigidbody* o)
{
	owner = o;
}

/**
 * @brief 获取拥有者
 * 
 * @return Rigidbody* 拥有者
 */
Rigidbody* Collider::getOwner() const
{
	return owner;
}
