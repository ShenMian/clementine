// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector4.h"
#include "Vector3.h"

namespace clem
{

Vector4::Vector4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(const Vector3& v, float w)
    : x(v.x), y(v.y), z(v.z), w(w)
{
}

} // namespace clem