// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector3.h"
#include "Vector2.h"
#include <cassert>
#include <cfloat>
#include <cmath>

namespace clem
{

const Vector3 Vector3::unit(1, 1, 1);
const Vector3 Vector3::unit_x(1, 0, 0);
const Vector3 Vector3::unit_y(0, 1, 0);
const Vector3 Vector3::unit_z(0, 0, 1);
const Vector3 Vector3::zero(0, 0, 0);

const Vector3 Vector3::up(0, 1, 0);
const Vector3 Vector3::down(0, -1, 0);
const Vector3 Vector3::right(-1, 0, 0);
const Vector3 Vector3::left(1, 0, 0);
const Vector3 Vector3::front(0, 0, -1);
const Vector3 Vector3::back(0, 0, -1);

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector2& v, float z)
    : x(v.x), y(v.y), z(z)
{
}

float Vector3::size() const
{
    return std::sqrt(sizeSquared());
}

float Vector3::sizeSquared() const
{
    return x * x + y * y + z * z;
}

float Vector3::distance(const Vector3& p) const
{
    return std::sqrt(distanceSquared(p));
}

float Vector3::distanceSquared(const Vector3& p) const
{
    const auto dx = std::abs(x - p.x);
    const auto dy = std::abs(y - p.y);
    const auto dz = std::abs(z - p.z);
    return dx * dx + dy * dy + dz * dz;
}

Vector3& Vector3::normalize()
{
    const auto len = size();
    if(len < FLT_EPSILON)
        return *this;
    return *this *= 1.0f / len;
}

float Vector3::dot(const Vector3& v) const
{
    return x * v.x + y * v.y;
}

void Vector3::rotate(const Vector3& point, float angle)
{
    const auto sinAngle = std::sin(angle);
    const auto cosAngle = std::cos(angle);

    if(point == Vector3::zero)
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

Vector3 Vector3::getMidPoint(const Vector3& p) const
{
    return Vector3((x + p.x) / 2.0f, (y + p.y) / 2.0f, (z + p.z) / 2.0f);
}
float& Vector3::operator[](size_t index)
{
    switch(index)
    {
    case 0:
        return x;

    case 1:
        return y;

    case 2:
        return z;

    default:
        assert(false);
        return x;
    }
}

bool Vector3::operator==(const Vector3& rhs) const
{
    return (std::abs(x - rhs.x) < FLT_EPSILON) &&
           (std::abs(y - rhs.y) < FLT_EPSILON) &&
           (std::abs(z - rhs.z) < FLT_EPSILON);
}

bool Vector3::operator!=(const Vector3& rhs) const
{
    return !(*this == rhs);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3& Vector3::operator*=(float n)
{
    return *this = *this * n;
}

Vector3& Vector3::operator/=(float n)
{
    return *this = *this / n;
}

Vector3 Vector3::operator*(float n) const
{
    return Vector3(x * n, y * n, z * n);
}

Vector3 Vector3::operator/(float n) const
{
    return Vector3(x / n, y / n, z / n);
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

} // namespace clem