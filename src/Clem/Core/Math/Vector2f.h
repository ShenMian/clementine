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
 * @brief 二维向量, 单精度.
 */
struct Vector2f
{
	float x = 0.0f;
	float y = 0.0f;

	/**
	 * @brief 默认构造函数.
	 */
	Vector2f() = default;

	/**
	 * @brief 构造函数.
	 * 
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Vector2f(float x, float y);

	/**
	 * @brief 获取长度.
	 * 
	 * @see sizeSquared
	 */
	float size() const;

	/**
	 * @brief 获取长度平方.
	 * 
	 * @see size
	 */
	float sizeSquared() const;

	/**
	 * @brief 获取到另一个点的距离.
	 * 
	 * @param point 另一个点.
	 * 
	 * @see	distanceSquared
	 */
	float distance(const Vector2f& point) const;

	/**
	 * @brief 获取到另一个点的距离的平方.
	 * 
	 * @param point 另一个点.
	 * 
	 * @see distance
	 */
	float distanceSquared(const Vector2f& point) const;

	/**
	 * @brief 标准化成单位向量.
	 */
	Vector2f& normalize();

	/**
	 * @brief 获取面积.
	 */
	float area() const;

	/**
	 * @brief 获取整型二维向量.
	 * 
	 * @return 当前向量去除小数后的整型二维向量.
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
