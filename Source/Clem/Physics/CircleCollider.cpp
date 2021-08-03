// Copyright 2021 SMS
// License(Apache-2.0)
// 圆形碰撞体

#include "CircleCollider.h"
#include <cassert>

namespace clem
{
CircleCollider::CircleCollider(float r)
    : radius(r)
{
}

void CircleCollider::setRadius(float r)
{
    radius = r;
}

float CircleCollider::getRadius() const
{
    return radius;
}
} // namespace clem