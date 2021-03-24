// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2f.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维矩形, 单精度.
 */
class Rect2f
{
public:
	Vector2f origin;
	Size2f   size;

	/**
	 * @brief 默认构造函数.
	 */
	Rect2f() = default;

	/**
	 * @brief 构造函数.
	 * 
	 * @param origin 坐标.
	 * @param size   大小.
	 */
	Rect2f(const Point2f& origin, Size2f size);

	/**
	 * @brief 构造函数.
	 * 
	 * @param x      x坐标.
	 * @param y      y坐标.
	 * @param width  宽.
	 * @param height 高.
	 */
	Rect2f(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point2f tl() const;
	Point2f tr() const;
	Point2f bl() const;
	Point2f br() const;

	bool containsPoint(const Point2f& point) const;
	bool intersectsRect(const Rect2f& rect) const;
};

using Rect2 = Rect2f;

/**
 * end of Math group
 * @}
 */
