// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_VEC2_H_
#define CLEM_MATH_VEC2_H_

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维向量.
 */
template <class T = float>
class Vec2
{
public:
	union
	{
		T x = 0;
		T width;
	};

	union
	{
		T y = 0;
		T height;
	};

	/**
	 * @brief 构造函数.
	 */
	Vec2() = default;

	/**
	 * @brief 构造函数.
	 *
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Vec2(T x, T y);

	/**
	 * @brief 获取长度.
	 *
	 * @see lengthSquared
	 */
	float length() const;

	/**
	 * @brief 获取长度平方.
	 *
	 * @see length
	 */
	inline float lengthSquared() const;

	/**
	 * @brief 标准化成单位向量.
	 */
	Vec2<T>& normalize();

	/**
	 * @brief 旋转向量绕定点一定角度(弧度制).
	 *
   * @param point 围绕旋转的点.
   * @param angle 要旋转的角度(弧度制).
	 */
	Vec2<T>& rotate(const Vector2& point, float angle);

	/**
	 * @brief 获取角度.
	 */
	float getAngle() const;

	/**
	 * @brief 获取到另一个点的距离.
	 *
	 * @param point 另一个点.
	 *
	 * @see	distanceSquared
	 */
	float distance(const Vec2<T>& point) const;

	/**
	 * @brief 获取到另一个点的距离的平方.
	 *
	 * @param point 另一个点.
	 *
	 * @see distance
	 */
	float distanceSquared(const Vec2<T>& point) const;

	/**
	 * @brief 获取两点之间的中点.
	 *
	 * @param point 另一个点.
	 */
	Vec2<T> getMidpoint(const Vec2<T>& point) const;

	/**
	 * @brief 裁剪到指定的范围内.
	 *
	 * @param min 最小值.
	 * @param max 最大值.
	 */
	void clamp(const Vec2<T>& min, const Vec2<T>& max);

	/**
	 * @brief 获取面积.
	 */
	float area() const;

	bool operator==(const Vec2<T>& v) const;
	bool operator!=(const Vec2<T>& v) const;

	Vec2<T>  operator*(float n) const;
	Vec2<T>  operator/(float n) const;
	Vec2<T>  operator+(const Vec2<T>& v) const;
	Vec2<T>  operator-(const Vec2<T>& v) const;
	Vec2<T>  operator-() const;
	Vec2<T>& operator+=(const Vec2<T>& v);
	Vec2<T>& operator-=(const Vec2<T>& v);
	Vec2<T>& operator*=(float n);
	Vec2<T>& operator/=(float n);

	operator Vector2i() const;
	operator Vector2() const;

	static const Vec2<T> zero;
};

#define Point2 Vec2
//using Point2 = Vec2;
using Size2 = Vector2;

#include "Vec2.inl"

/**
 * end of Math group
 * @}
 */

#endif // !CLEM_MATH_VEC2_H_
