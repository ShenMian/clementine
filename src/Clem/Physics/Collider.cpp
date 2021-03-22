﻿// Copyright 2021 SMS
// License(Apache-2.0)
// 碰撞体

#include "Collider.h"
#include "Rigidbody.h"
#include <cassert>

Point Collider::getPosition() const
{
	// assert(owner);
	return Point(); // owner->getOwner()->getPosition() + offset;
}

void Collider::setOffset(Point o)
{
	offset = o;
}

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