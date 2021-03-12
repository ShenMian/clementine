// Copyright 2020 SMS
// License(Apache-2.0)
// 圆形碰撞体

#ifndef CLEM_CIRCLE_COLLIDER_H_
#define CLEM_CIRCLE_COLLIDER_H_

#include "collider.h"

/// 圆形碰撞体
class CircleCollider : public Collider
{
public:
	void  setRadius(float);
	float getRadius() const;

private:
	float radius;
};

#endif // !CLEM_CIRCLE_COLLIDER_H_
