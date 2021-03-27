// Copyright 2021 SMS
// License(Apache-2.0)
// 盒形碰撞体

#include "BoxCollider.h"
#include <cassert>

BoxCollider::BoxCollider(Size2 size)
		: size(size)
{
}

void BoxCollider::setSize(Size2 s)
{
	size = s;
}

Size2 BoxCollider::getSize() const
{
	return size;
}

Rect2 BoxCollider::getRect() const
{
	auto p = getPosition();
	return Rect2({p.x - size.x / 2, p.y - size.y / 2}, size);
}