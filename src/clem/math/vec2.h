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
	 * @brief 构造函数.
	 */
	Vec2();

	/**
	 * @brief 构造函数.
	 * 
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Vec2(float x, float y);

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
	Vec2& normalize();

	/**
	 * @brief 旋转向量绕定点一定角度(弧度制).
	 * 
   * @param point 围绕旋转的点.
   * @param angle 要旋转的角度(弧度制).
	 */
	Vec2& rotate(const Vec2& point, float angle);

	/**
	 * @brief 获取角度.
	 */
	float getAngle() const;

	/**
	 * @brief 裁剪到指定的范围内.
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

	static const Vec2 zero;
};

/**
 * end of math group
 * @}
 */

#endif // !CLEM_MATH_VEC2_H_
