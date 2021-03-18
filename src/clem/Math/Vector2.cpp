// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector2.h"
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>

Vector2::Vector2(float x, float y)
		: x(x), y(y)
{
}

float Vector2::length() const
{
	return std::sqrt(lengthSquared());
}

float Vector2::lengthSquared() const
{
	return x * x + y * y;
}

Vector2& Vector2::normalize()
{
	const auto len = length();
	if(len < FLT_EPSILON)
		return *this;
	return *this *= 1.0f / len;
}

Vector2& Vector2::rotate(const Vector2& point, float angle)
{
	const float sinAngle = std::sin(angle);
	const float cosAngle = std::cos(angle);

	if(point == Vector2(0, 0))
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

float Vector2::getAngle() const
{
	return std::atan2(y, x);
}

float Vector2::distance(const Vector2& p) const
{
	return std::sqrt(distanceSquared(p));
}

float Vector2::distanceSquared(const Vector2& p) const
{
	auto xDis = std::abs(x - p.x);
	auto yDis = std::abs(y - p.y);
	return xDis * xDis + yDis * yDis;
}

Point Vector2::getMidpoint(const Vector2& p) const
{
	return (*this + p) / 2.0f;
}

void Vector2::clamp(const Vector2& min, const Vector2& max)
{
	assert(min.x <= max.x && min.y <= max.y);

	x = std::max(x, min.x);
	x = std::min(x, max.x);
	y = std::max(y, min.y);
	y = std::min(y, max.y);
}

float Vector2::area() const
{
	return width * height;
}

bool Vector2::operator==(const Vector2& v) const
{
	return (std::abs(x - v.x) < FLT_EPSILON) &&
				 (std::abs(y - v.y) < FLT_EPSILON);
}

bool Vector2::operator!=(const Vector2& v) const
{
	return !(*this == v);
}

Vector2 Vector2::operator*(float n) const
{
	return Vector2(x * n, y * n);
}

Vector2 Vector2::operator/(float n) const
{
	return Vector2(x / n, y / n);
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
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

const Vector2 Vector2::zero(0, 0);
