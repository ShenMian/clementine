// Copyright 2021 SMS
// License(Apache-2.0)

#include "Collider.h"
#include "Rigidbody.h"
#include <cassert>

namespace clem
{

void Collider::setOffset(Point3 o)
{
    offset = o;
}

const Point3& Collider::getOffset() const
{
    return offset;
}

} // namespace clem