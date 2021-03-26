// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vec2.h"
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>

template <class T>
Vec2<T>::Vec2(T x_, T y_)
		: x(x_), y(y_)
{
}

template <class T>
float Vec2<T>::length() const
{
	return std::sqrt(lengthSquared());
}

template <class T>
float Vec2<T>::lengthSquared() const
{
	return x * x + y * y;
}

template <class T>
Vec2<T>& Vec2<T>::normalize()
{
	const auto len = length();
	if(len < FLT_EPSILON)
		return *this;
	return *this *= 1.0f / len;
}

template <class T>
Vec2<T>& Vec2<T>::rotate(const Vector2& point, float angle)
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

template <class T>
float Vec2<T>::getAngle() const
{
	return std::atan2(y, x);
}

template <class T>
float Vec2<T>::distance(const Vec2<T>& p) const
{
	return std::sqrt(distanceSquared(p));
}

template <class T>
float Vec2<T>::distanceSquared(const Vec2<T>& p) const
{
	auto xDis = std::abs(x - p.x);
	auto yDis = std::abs(y - p.y);
	return xDis * xDis + yDis * yDis;
}

template <class T>
Vec2<T> Vec2<T>::getMidpoint(const Vec2<T>& p) const
{
	return (*this + p) / 2.0f;
}

template <class T>
void Vec2<T>::clamp(const Vec2<T>& min, const Vec2<T>& max)
{
	assert(min.x <= max.x && min.y <= max.y);

	x = std::max(x, min.x);
	x = std::min(x, max.x);
	y = std::max(y, min.y);
	y = std::min(y, max.y);
}

template <class T>
float Vec2<T>::area() const
{
	return width * height;
}

template <class T>
bool Vec2<T>::operator==(const Vec2<T>& v) const
{
	return (std::abs(x - v.x) < FLT_EPSILON) &&
				 (std::abs(y - v.y) < FLT_EPSILON);
}

template <class T>
bool Vec2<T>::operator!=(const Vec2<T>& v) const
{
	return !(*this == v);
}

template <class T>
Vec2<T> Vec2<T>::operator*(float n) const
{
	return Vector2(x * n, y * n);
}

template <class T>
Vec2<T> Vec2<T>::operator/(float n) const
{
	return Vector2(x / n, y / n);
}

template <class T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& v) const
{
	return Vector2(x + v.x, y + v.y);
}

template <class T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& v) const
{
	return Vector2(x - v.x, y - v.y);
}

template <class T>
Vec2<T> Vec2<T>::operator-() const
{
	return Vector2(-x, -y);
}

template <class T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

template <class T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

template <class T>
Vec2<T>& Vec2<T>::operator*=(float n)
{
	return *this = *this * n;
}

template <class T>
Vec2<T>& Vec2<T>::operator/=(float n)
{
	return *this = *this / n;
}

template <class T>
Vec2<T>::operator Vector2i() const
{
	return Vector2i(static_cast<int>(x), static_cast<int>(y));
}

template <class T>
Vec2<T>::operator Vector2() const
{
	return Vector2(static_cast<float>(x), static_cast<float>(y));
}

template <class T>
const Vec2<T> Vec2<T>::zero(0, 0);
