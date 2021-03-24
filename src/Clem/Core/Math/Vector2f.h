// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

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
	 * @brief ��ȡ���.
	 */
	float area() const;

	/**
	 * @brief ��ȡ���Ͷ�ά����.
	 * 
	 * @return ��ǰ����ȥ��С��������Ͷ�ά����.
	 */
	Vector2i asInt() const;

	operator Vector2i() const;

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

	Vector2f operator+(const Vector2i& v) const;
	Vector2f operator-(const Vector2i& v) const;

	static const Vector2f Zero; // (0, 0)
	static const Vector2f Unit; // (1, 1)
};

using Vector2 = Vector2f;
using Point2  = Vector2f;
using Size2   = Vector2f;
using Point2f = Vector2f;
using Size2f  = Vector2f;

/**
 * end of Math group
 * @}
 */
