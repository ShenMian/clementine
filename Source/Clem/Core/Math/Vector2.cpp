// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector2.h"

#include <cfloat>
#include <cmath>

const Vector2 Vector2::zero(0, 0);
const Vector2 Vector2::unit(1, 1);

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
	return std::sqrt(x * x + y * y);
}

float Vector2::magnitude() const
{
	return std::sqrt(x * x + y * y);
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
	auto xDis = std::abs(x - p.x);
	auto yDis = std::abs(y - p.y);
	return xDis * xDis + yDis * yDis;
}

Vector2& Vector2::normalize()
{
	const auto len = size();
	if(len < FLT_EPSILON)
		return *this;
	return *this *= 1.0f / len;
}

float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::angle() const
{
	return std::atan2(y, x);
}

Vector2 Vector2::getMidPoint(const Vector2& p) const
{
	return Vector2((x + p.x) / 2.0f, (y + p.y) / 2.0f);
}

float Vector2::area() const
{
	return x * y;
}

Vector2i Vector2::asInt() const
{
	return Vector2i(static_cast<int>(x), static_cast<int>(y));
}

Vector2::operator Vector2i() const
{
	return asInt();
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

Vector2 Vector2::operator+(const Vector2i& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2i& v) const
{
	return Vector2(x - v.x, y - v.y);
}