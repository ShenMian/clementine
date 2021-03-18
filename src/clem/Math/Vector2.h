// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_VECTOR2_H_
#define CLEM_MATH_VECTOR2_H_

/**
 * @addtogroup Math
 * @{
 */

/**
 * 二维向量.
 */
class Vector2
{
public:
	union
	{
		float x = 0;
		float width;
	};

	union
	{
		float y = 0;
		float height;
	};

	/**
	 * @brief 构造函数.
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
	Vector2& normalize();

	/**
	 * @brief 旋转向量绕定点一定角度(弧度制).
	 * 
   * @param point 围绕旋转的点.
   * @param angle 要旋转的角度(弧度制).
	 */
	Vector2& rotate(const Vector2& point, float angle);

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
	float distance(const Vector2& point) const;

	/**
	 * @brief 获取到另一个点的距离的平方.
	 * 
	 * @param point 另一个点.
	 * 
	 * @see distance
	 */
	float distanceSquared(const Vector2& point) const;

	/**
	 * @brief 获取两点之间的中点.
	 * 
	 * @param point 另一个点.
	 */
	Vector2 getMidpoint(const Vector2& point) const;

	/**
	 * @brief 裁剪到指定的范围内.
	 * 
	 * @param min 最小值.
	 * @param max 最大值.
	 */
	void clamp(const Vector2& min, const Vector2& max);

	/**
	 * @brief 获取面积.
	 */
	float area() const;

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	Vector2  operator*(float n) const;
	Vector2  operator/(float n) const;
	Vector2  operator+(const Vector2& v) const;
	Vector2  operator-(const Vector2& v) const;
	Vector2  operator-() const;
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float n);
	Vector2& operator/=(float n);

	static const Vector2 zero;
};

typedef Vector2 Point;
typedef Vector2 Size;

/**
 * end of Math group
 * @}
 */

#endif // !CLEM_MATH_VECTOR2_H_
