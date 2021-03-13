// Copyright 2020 SMS
// License(Apache-2.0)
// 碰撞体

#include "collider.h"
#include "rigidbody.h"

Collider::Collider()
		: owner(nullptr)
{
}

Collider::~Collider()
{
}

/**
 * @brief 获取坐标
 * 
 * @return Point 坐标
 */
Point Collider::getPosition() const
{
	return owner->getOwner()->getPosition() + offset;
}

/**
 * @brief 设置偏移
 * 
 * @param o 偏移
 */
void Collider::setOffset(Point o)
{
	offset = o;
}

/**
 * @brief 获取偏移
 * 
 * @return Point 偏移
 */
Point Collider::getOffset() const
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
