// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector2f.h"

#include <cfloat>
#include <cmath>

const Vector2f Vector2f::Zero(0, 0);
const Vector2f Vector2f::Unit(1, 1);

Vector2f::Vector2f(float x, float y)
		: x(x), y(y)
{
}

float Vector2f::size() const
{
	return std::sqrt(sizeSquared());
}

float Vector2f::sizeSquared() const
{
	return x * x + y * y;
}

float Vector2f::distance(const Vector2f& p) const
{
	return std::sqrt(distanceSquared(p));
}

float Vector2f::distanceSquared(const Vector2f& p) const
{
	auto xDis = std::abs(x - p.x);
	auto yDis = std::abs(y - p.y);
	return xDis * xDis + yDis * yDis;
}

Vector2f& Vector2f::normalize()
{
	const auto len = size();
	if(len < FLT_EPSILON)
		return *this;
	return *this *= 1.0f / len;
}

float Vector2f::area() const
{
	return x * y;
}

Vector2i Vector2f::asInt() const
{
	return Vector2i(static_cast<int>(x), static_cast<int>(y));
}

Vector2f::operator Vector2i() const
{
	return asInt();
}

bool Vector2f::operator==(const Vector2f& v) const
{
	return (std::abs(x - v.x) < FLT_EPSILON) &&
				 (std::abs(y - v.y) < FLT_EPSILON);
}

bool Vector2f::operator!=(const Vector2f& v) const
{
	return !(*this == v);
}


Vector2f Vector2f::operator*(float n) const
{
	return Vector2f(x * n, y * n);
}


Vector2f Vector2f::operator/(float n) const
{
	return Vector2f(x / n, y / n);
}


Vector2f Vector2f::operator+(const Vector2f& v) const
{
	return Vector2f(x + v.x, y + v.y);
}


Vector2f Vector2f::operator-(const Vector2f& v) const
{
	return Vector2f(x - v.x, y - v.y);
}


Vector2f Vector2f::operator-() const
{
	return Vector2f(-x, -y);
}


Vector2f& Vector2f::operator+=(const Vector2f& v)
{
	x += v.x;
	y += v.y;
	return *this;
}


Vector2f& Vector2f::operator-=(const Vector2f& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}


Vector2f& Vector2f::operator*=(float n)
{
	return *this = *this * n;
}


Vector2f& Vector2f::operator/=(float n)
{
	return *this = *this / n;
}

Vector2f Vector2f::operator+(const Vector2i& v) const
{
	return Vector2f(x + v.x, y + v.y);
}

Vector2f Vector2f::operator-(const Vector2i& v) const
{
	return Vector2f(x - v.x, y - v.y);
}
