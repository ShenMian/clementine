// Copyright 2020 SMS
// License(Apache-2.0)
// 盒形碰撞体

#include "box_collider.h"
#include "circle_collider.h"
#include <cassert>

/**
 * @brief 检测是否与其他碰撞体发生碰撞
 * 
 * @param other 其他碰撞体
 * @return true 发生碰撞
 * @return false 未发生碰撞
 */
bool BoxCollider::collides(const Collider& other) const
{
	if(auto o = dynamic_cast<const BoxCollider*>(&other))
		return getRect().contains(o->getRect());
	else if(auto o = dynamic_cast<const CircleCollider*>(&other))
		assert(false);
	else
		assert(false);
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
