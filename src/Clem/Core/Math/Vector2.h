﻿// Copyright 2021 SMS
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
struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	/**
	 * @brief 默认构造函数.
	 */
	Vector2() = default;

	/**
	 * @brief 构造函数.
	 *
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Vector2(float x, float y);

	/**
	 * @brief 获取长度.
	 *
	 * @see sizeSquared
	 */
	float size() const;

	/**
	 * @brief 获取长度.
	 *
	 * @see size
	 */
	float magnitude() const;

	/**
	 * @brief 获取长度平方.
	 *
	 * @see size
	 */
	float sizeSquared() const;

	/**
	 * @brief 获取到另一个点的距离.
	 *
	 * @param p 另一个点.
	 *
	 * @see	distanceSquared
	 */
	float distance(const Vector2& p) const;

	/**
	 * @brief 获取到另一个点的距离的平方.
	 *
	 * @param p 另一个点.
	 *
	 * @see distance
	 */
	float distanceSquared(const Vector2& p) const;

	/**
	 * @brief 标准化成单位向量.
	 */
	Vector2& normalize();

	/**
	 * @brief 计算向量点积.
	 *
	 * @param v 另一个向量.
	 * @return 和另一个向量的点积.
	 */
	float dot(const Vector2& v) const;

	/**
	 * @brief 获取角度.
	 *
	 * @return 角度, 弧度制.
	 */
	float getAngle() const;

	/**
	 * @brief 获取与另一个点之间的中点.
	 */
	Vector2 getMidPoint(const Vector2& p) const;

	/**
	 * @brief 获取面积.
	 */
	float area() const;

	/**
	 * @brief 获取整型二维向量.
	 *
	 * @return 去除小数后的整型二维向量.
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

	static const Vector2 zero; // (0, 0)
	static const Vector2 unit; // (1, 1)

	static const Vector2 up;    // (0, 1)
	static const Vector2 down;  // (0, -1)
	static const Vector2 right; // (1, 0)
	static const Vector2 left;  // (-1, 0)
};

using Point2 = Vector2;
using Size2  = Vector2;

/**
 * end of Math group
 * @}
 */
