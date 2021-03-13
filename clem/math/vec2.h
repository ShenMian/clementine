// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_VEC2_H_
#define CLEM_MATH_VEC2_H_

#include <cmath>
#include <cfloat>

class Point;

/**
 * @addtogroup math
 * @{
 */

/**
 * 二维向量.
 */
class Vec2
{
public:
	float x, y;

	/**
	 * 构造函数.
	 */
	Vec2();

	/**
	 * 构造函数.
	 * 
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Vec2(float x, float y);

	/**
	 * 获取长度.
	 * 
	 * @see lengthSquared
	 */
	float length() const;

	/**
	 * 获取长度平方.
	 * 
	 * @see length
	 */
	inline float lengthSquared() const;

	void normalize();

	/**
	 * 裁剪.
	 * 
	 * @param min 最小值.
	 * @param max 最大值.
	 */
	void clamp(Point min, Point max);

	bool  operator==(const Vec2& v) const;
	bool  operator!=(const Vec2& v) const;

	Vec2  operator*(float n) const;
	Vec2  operator/(float n) const;
	Vec2  operator+(const Vec2& v) const;
	Vec2  operator-(const Vec2& v) const;
	Vec2  operator-() const;
	Vec2& operator+=(const Vec2& v);
	Vec2& operator-=(const Vec2& v);
	Vec2& operator*=(float n);
	Vec2& operator/=(float n);
};

/**
 * end of math group
 * @}
 */

#endif // !CLEM_MATH_VEC2_H_
