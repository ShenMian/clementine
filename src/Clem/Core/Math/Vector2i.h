// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief ��ά����, ����.
 */
struct Vector2i
{
	int x = 0;
	int y = 0;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Vector2i() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param x x����.
	 * @param y y����.
	 */
	Vector2i(int x, int y);

	/**
	 * @brief ��ȡ���.
	 */
	int area() const;

	bool      operator==(const Vector2i& v) const;
	bool      operator!=(const Vector2i& v) const;
	Vector2i  operator*(float n) const;
	Vector2i  operator/(float n) const;
	Vector2i  operator+(const Vector2i& v) const;
	Vector2i  operator-(const Vector2i& v) const;
	Vector2i  operator-() const;
	Vector2i& operator+=(const Vector2i& v);
	Vector2i& operator-=(const Vector2i& v);
	Vector2i& operator*=(float n);
	Vector2i& operator/=(float n);
};

using Point2i = Vector2i;
using Size2i  = Vector2i;

/**
 * end of Math group
 * @}
 */
