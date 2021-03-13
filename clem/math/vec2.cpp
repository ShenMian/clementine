// Copyright 2021 SMS
// License(Apache-2.0)

#include "vec2.h"
#include "point.h"
#include <cmath>
#include <cfloat>
#include <algorithm>

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

void Vec2::normalize()
{
	const auto len = length();
	if(len < FLT_EPSILON)
		return;
	*this *= 1.0 / len;
}

void Vec2::clamp(Point min, Point max)
{
	x = std::min(x, min.x);
	x = std::max(x, max.x);
	y = std::min(y, min.y);
	y = std::max(y, max.y);
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
