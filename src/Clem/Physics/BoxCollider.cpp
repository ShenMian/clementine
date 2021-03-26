// Copyright 2021 SMS
// License(Apache-2.0)
// 盒形碰撞体

#include "BoxCollider.h"
#include <cassert>

BoxCollider::BoxCollider(Size2 size)
		: size(size)
{
}

/**
 * @brief 设置大小
 *
 * @param s 大小
 */
void BoxCollider::setSize(Size2 s)
{
	size = s;
}

/**
 * @brief 获取大小
 *
 * @return Size2 大小
 */
Size2 BoxCollider::getSize() const
{
	return size;
}

Rect2 BoxCollider::getRect() const
{
	auto p = getPosition();
	return Rect2({p.x - size.x / 2, p.y - size.y / 2}, size);
}