// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vec2.h"
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>

Vec2::Vec2(float x_, float y_)
		: x(x_), y(y_)
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
	const float sinAngle = std::sin(angle);
	const float cosAngle = std::cos(angle);

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

float Vec2::distance(const Vec2& p) const
{
	return std::sqrt(distanceSquared(p));
}

float Vec2::distanceSquared(const Vec2& p) const
{
	auto xDis = std::abs(x - p.x);
	auto yDis = std::abs(y - p.y);
	return xDis * xDis + yDis * yDis;
}

Point Vec2::getMidpoint(const Vec2& p) const
{
	return (*this + p) / 2.0f;
}

void Vec2::clamp(const Vec2& min, const Vec2& max)
{
	assert(min.x <= max.x && min.y <= max.y);

	x = std::max(x, min.x);
	x = std::min(x, max.x);
	y = std::max(y, min.y);
	y = std::min(y, max.y);
}

float Vec2::area() const
{
	return width * height;
}

bool Vec2::operator==(const Vec2& v) const
{
	return (std::abs(x - v.x) < FLT_EPSILON) &&
				 (std::abs(y - v.y) < FLT_EPSILON);
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
