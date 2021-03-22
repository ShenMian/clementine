// Copyright 2021 SMS
// License(Apache-2.0)
// 盒形碰撞体

#include "BoxCollider.h"
#include <cassert>

BoxCollider::BoxCollider(Size size)
		: size(size)
{
}

/**
 * @brief 设置大小
 * 
 * @param s 大小
 */
void BoxCollider::setSize(Size s)
{
	size = s;
}

/**
 * @brief 获取大小
 * 
 * @return Size 大小
 */
Size BoxCollider::getSize() const
{
	return size;
}

Rect BoxCollider::getRect() const
{
	auto p = getPosition();
	return Rect({p.x - size.x / 2, p.y - size.y / 2}, size);
}
