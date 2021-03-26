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
struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Vector2() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param x x����.
	 * @param y y����.
	 */
	Vector2(float x, float y);

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
	float distance(const Vector2& point) const;

	/**
	 * @brief ��ȡ����һ����ľ����ƽ��.
	 * 
	 * @param point ��һ����.
	 * 
	 * @see distance
	 */
	float distanceSquared(const Vector2& point) const;

	/**
	 * @brief ��׼���ɵ�λ����.
	 */
	Vector2& normalize();

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

	bool     operator==(const Vector2& v) const;
	bool     operator!=(const Vector2& v) const;
	Vector2  operator*(float n) const;
	Vector2  operator/(float n) const;
	Vector2  operator+(const Vector2& v) const;
	Vector2  operator-(const Vector2& v) const;
	Vector2  operator-() const;
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float n);
	Vector2& operator/=(float n);

	Vector2 operator+(const Vector2i& v) const;
	Vector2 operator-(const Vector2i& v) const;

	static const Vector2 Zero; // (0, 0)
	static const Vector2 Unit; // (1, 1)
};

using Point2 = Vector2;
using Size2  = Vector2;

/**
 * end of Math group
 * @}
 */
