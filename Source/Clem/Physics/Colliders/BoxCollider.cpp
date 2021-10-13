// Copyright 2021 SMS
// License(Apache-2.0)
// 盒形碰撞体

#include "BoxCollider.h"
#include <cassert>

namespace clem
{

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

} // namespace clem