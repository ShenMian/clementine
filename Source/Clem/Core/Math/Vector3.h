// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cfloat>
#include <cmath>

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 三维向量, 单精度浮点数.
 */
class Vector3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	/**
	 * @brief 默认构造函数.
	 */
	Vector3() = default;

	/**
	 * @brief 构造函数.
	 *
	 * @param x x坐标.
	 * @param y y坐标.
	 * @param z z坐标.
	 */
	Vector3(float x, float y, float z);

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
	float distance(const Vector3& point) const;

	/**
	 * @brief 获取到另一个点的距离的平方.
	 *
	 * @param point 另一个点.
	 *
	 * @see distance
	 */
	float distanceSquared(const Vector3& point) const;

	/**
	 * @brief 标准化成单位向量.
	 */
	Vector3& normalize();

	/**
	 * @brief 计算向量点积.
	 *
	 * @param v 另一个向量.
	 * @return 和另一个向量的点积.
	 */
	float dot(const Vector3& v) const;

	/**
	 * @brief 获取角度.
	 *
	 * @return 角度, 弧度制. 范围: [2π, -2π)
	 */
	float angle() const;

	/**
	 * @brief 围绕指定点旋转指定弧度.
	 *
	 * @param point 点.
	 * @param angle 旋转角度, 弧度制.
	 */
	void rotate(const Vector3& point, float angle);

	/**
	 * @brief 获取与另一个点之间的中点.
	 */
	Vector3 getMidPoint(const Vector3& p) const;

	float&   operator[](size_t index);
	bool     operator==(const Vector3& v) const;
	bool     operator!=(const Vector3& v) const;
	Vector3  operator*(float n) const;
	Vector3  operator/(float n) const;
	Vector3  operator+(const Vector3& v) const;
	Vector3  operator-(const Vector3& v) const;
	Vector3  operator-() const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float n);
	Vector3& operator/=(float n);

	static const Vector3 unit; // (1, 1, 1)
	static const Vector3 zero; // (0, 0, 0)

	static const Vector3 up;    // (0, 0, 1)
	static const Vector3 down;  // (0, 0, -1)
	static const Vector3 right; // ()
	static const Vector3 left;  // ()
	static const Vector3 front; // ()
	static const Vector3 back;  // ()
};

using Point3 = Vector3;
using Vec3   = Vector3;

/**
 * end of Math group
 * @}
 */
