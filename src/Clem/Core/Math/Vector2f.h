// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <algorithm>
#include <cfloat>
#include <cmath>

#include "Vector2i.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief ��ά����, ������.
 */
struct Vector2f
{
	float x = 0.0f;
	float y = 0.0f;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Vector2f() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param x x����.
	 * @param y y����.
	 */
	Vector2f(float x, float y);

	/**
	 * @brief ��ȡ����.
	 * 
	 * @see sizeSquared
	 */
	float size() const;

	/**
	 * @brief ��ȡ����ƽ��.
	 * 
	 * @see size
	 */
	float sizeSquared() const;

	/**
	 * @brief ��ȡ����һ����ľ���.
	 * 
	 * @param point ��һ����.
	 * 
	 * @see	distanceSquared
	 */
	float distance(const Vector2f& point) const;

	/**
	 * @brief ��ȡ����һ����ľ����ƽ��.
	 * 
	 * @param point ��һ����.
	 * 
	 * @see distance
	 */
	float distanceSquared(const Vector2f& point) const;

	/**
	 * @brief ��׼���ɵ�λ����.
	 */
	Vector2f& normalize();

	/**
	 * @brief ��ȡ���Ͷ�ά����.
	 * 
	 * @return ��ǰ����ȥ��С��������Ͷ�ά����.
	 */
	Vector2i asInt() const;

	bool      operator==(const Vector2f& v) const;
	bool      operator!=(const Vector2f& v) const;
	Vector2f  operator*(float n) const;
	Vector2f  operator/(float n) const;
	Vector2f  operator+(const Vector2f& v) const;
	Vector2f  operator-(const Vector2f& v) const;
	Vector2f  operator-() const;
	Vector2f& operator+=(const Vector2f& v);
	Vector2f& operator-=(const Vector2f& v);
	Vector2f& operator*=(float n);
	Vector2f& operator/=(float n);

	static const Vector2f Zero; // (0, 0)
	static const Vector2f Unit; // (1, 1)
};

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

Vector2i Vector2f::asInt() const
{
	return Vector2i(x, y);
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

using Vector2 = Vector2f;
using Point2  = Vector2f;
using Size2   = Vector2f;
using Point2f = Vector2f;
using Size2f  = Vector2f;
using Point2i = Vector2i;
using Size2i  = Vector2i;

/**
 * end of Math group
 * @}
 */
