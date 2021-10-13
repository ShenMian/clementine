// Copyright 2021 SMS
// License(Apache-2.0)

#include "SphereCollider.h"
#include <cassert>

namespace clem
{

SphereCollider::SphereCollider(float r)
    : radius(r)
{
}

void SphereCollider::setRadius(float r)
{
    radius = r;
}

float SphereCollider::getRadius() const
{
    return radius;
}

} // namespace clem