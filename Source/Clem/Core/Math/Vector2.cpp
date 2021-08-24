// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector2.h"
#include <cassert>
#include <cfloat>
#include <cmath>
#include <limits>

namespace clem
{

const Vector2 Vector2::unit(1, 1);
const Vector2 Vector2::unit_x(1, 0);
const Vector2 Vector2::unit_y(0, 1);
const Vector2 Vector2::zero(0, 0);

const Vector2 Vector2::up(0, 1);
const Vector2 Vector2::down(0, -1);
const Vector2 Vector2::right(1, 0);
const Vector2 Vector2::left(-1, 0);

Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
}

float Vector2::size() const
{
    return std::sqrt(sizeSquared());
}

float Vector2::sizeSquared() const
{
    return x * x + y * y;
}

float Vector2::distance(const Vector2& p) const
{
    return std::sqrt(distanceSquared(p));
}

float Vector2::distanceSquared(const Vector2& p) const
{
    const auto dx = std::abs(x - p.x);
    const auto dy = std::abs(y - p.y);
    return dx * dx + dy * dy;
}

Vector2& Vector2::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<float>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

float Vector2::dot(const Vector2& v) const
{
    return x * v.x + y * v.y;
}

float Vector2::cross(const Vector2& v) const
{
    return x * v.y - y * v.x;
}

float Vector2::angle() const
{
    return std::atan2(y, x);
}

void Vector2::rotate(const Vector2& point, float angle)
{
    const auto sinAngle = std::sin(angle);
    const auto cosAngle = std::cos(angle);

    if(point == Vector2::zero)
    {
        const auto tempX = x * cosAngle - y * sinAngle;
        y                = y * cosAngle + x * sinAngle;
        x                = tempX;
    }
    else
    {
        const auto tempX = x - point.x;
        const auto tempY = y - point.y;

        x = tempX * cosAngle - tempY * sinAngle + point.x;
        y = tempY * cosAngle + tempX * sinAngle + point.y;
    }
}

Vector2 Vector2::getMidPoint(const Vector2& p) const
{
    return Vector2((x + p.x) / 2.f, (y + p.y) / 2.f);
}

float Vector2::area() const
{
    return x * y;
}

float& Vector2::operator[](size_t index)
{
    switch(index)
    {
    case 0:
        return x;

    case 1:
        return y;

    default:
        assert(false);
        return x;
    }
}

bool Vector2::operator==(const Vector2& rhs) const
{
    return (std::abs(x - rhs.x) < FLT_EPSILON) &&
           (std::abs(y - rhs.y) < FLT_EPSILON);
}

bool Vector2::operator!=(const Vector2& rhs) const
{
    return !(*this == rhs);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(float n)
{
    return *this = *this * n;
}

Vector2& Vector2::operator/=(float n)
{
    return *this = *this / n;
}

Vector2 Vector2::operator*(float n) const
{
    return Vector2(x * n, y * n);
}

Vector2 Vector2::operator/(float n) const
{
    return Vector2(x / n, y / n);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2i& rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2i& rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2::operator Vector2i() const
{
    return Vector2i(static_cast<int>(x), static_cast<int>(y));
}

} // namespace clem