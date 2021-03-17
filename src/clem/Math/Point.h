// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_POINT_H_
#define CLEM_MATH_POINT_H_

class Vec2;

/**
 * @addtogroup Math
 * @{
 */

/**
 * 二维点.
 */
class Point
{
public:
	float x = 0;
	float y = 0;

	/**
	 * @brief 构造函数.
	 */
	Point() = default;

	/**
	 * @brief 构造函数.
	 * 
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Point(float x, float y);

	/**
	 * @brief 获取到另一个点的距离.
	 * 
	 * @param other 另一个点.
	 * 
	 * @see	distanceSquared
	 */
	float distance(const Point& other) const;

	/**
	 * @brief 获取到另一个点的距离的平方.
	 * 
	 * @param other 另一个点.
	 * 
	 * @see distance
	 */
	float distanceSquared(const Point& other) const;

	/**
	 * @brief 裁剪到指定的范围内.
	 * 
	 * @param min 最小值.
	 * @param max 最大值.
	 */
	void clamp(Point min, Point max);

	/**
	 * @brief 获取两点之间的中点.
	 * 
	 * @param other 另一个点.
	 */
	Point getMidpoint(const Point& other) const;

	Point  operator+(const Point&) const;
	Point  operator-(const Point&) const;
	Point  operator+(const Vec2&) const;
	Point  operator-(const Vec2&) const;
	Point& operator+=(const Vec2&);
	Point& operator-=(const Vec2&);
};

/**
 * end of Math group
 * @}
 */

#endif // !CLEM_MATH_POINT_H_
