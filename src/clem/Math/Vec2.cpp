// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vec2.h"
#include "Point.h"
#include <cmath>
#include <cfloat>

Vec2::Vec2()
		: x(0), y(0)
{
}

Vec2::Vec2(float x, float y)
		: x(x), y(y)
{
}

float Vec2::length() const
{
	return std::sqrt(lengthSquared());
}

float Vec2::lengthSquared() const
{
	return x * x + y * y;
}

Vec2& Vec2::normalize()
{
	const auto len = length();
	if(len < FLT_EPSILON)
		return *this;
	return *this *= 1.0f / len;
}

Vec2& Vec2::rotate(const Vec2& point, float angle)
{
	float sinAngle = std::sin(angle);
	float cosAngle = std::cos(angle);

	if(point == Vec2(0, 0))
	{
		float tempX = x * cosAngle - y * sinAngle;
		y           = y * cosAngle + x * sinAngle;
		x           = tempX;
	}
	else
	{
		float tempX = x - point.x;
		float tempY = y - point.y;

		x = tempX * cosAngle - tempY * sinAngle + point.x;
		y = tempY * cosAngle + tempX * sinAngle + point.y;
	}

	return *this;
}

float Vec2::getAngle() const
{
	return std::atan2(y, x);
}

bool Vec2::operator==(const Vec2& v) const
{
	return x == v.x && y == v.y;
}

bool Vec2::operator!=(const Vec2& v) const
{
	return !(*this == v);
}

Vec2 Vec2::operator*(float n) const
{
	return Vec2(x * n, y * n);
}

Vec2 Vec2::operator/(float n) const
{
	return Vec2(x / n, y / n);
}

Vec2 Vec2::operator+(const Vec2& v) const
{
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const
{
	return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2& Vec2::operator*=(float n)
{
	return *this = *this * n;
}

Vec2& Vec2::operator/=(float n)
{
	return *this = *this / n;
}

const Vec2 Vec2::zero(0, 0);
