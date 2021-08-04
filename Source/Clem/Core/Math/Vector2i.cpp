// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector2.h"

#include <cfloat>
#include <cmath>

namespace clem
{

Vector2i::Vector2i(int x, int y)
    : x(x), y(y)
{
}

int Vector2i::area() const
{
    return x * y;
}

bool Vector2i::operator==(const Vector2i& v) const
{
    return (std::abs(x - v.x) < FLT_EPSILON) &&
           (std::abs(y - v.y) < FLT_EPSILON);
}

bool Vector2i::operator!=(const Vector2i& v) const
{
    return !(*this == v);
}

Vector2i Vector2i::operator*(int n) const
{
    return Vector2i(x * n, y * n);
}

Vector2i Vector2i::operator/(int n) const
{
    return Vector2i(x / n, y / n);
}

Vector2i Vector2i::operator+(const Vector2i& v) const
{
    return Vector2i(x + v.x, y + v.y);
}

Vector2i Vector2i::operator-(const Vector2i& v) const
{
    return Vector2i(x - v.x, y - v.y);
}

Vector2i Vector2i::operator-() const
{
    return Vector2i(-x, -y);
}

Vector2i& Vector2i::operator+=(const Vector2i& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2i& Vector2i::operator*=(int n)
{
    return *this = *this * n;
}

Vector2i& Vector2i::operator/=(int n)
{
    return *this = *this / n;
}

} // namespace clem