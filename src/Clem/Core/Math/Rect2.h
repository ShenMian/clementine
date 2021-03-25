// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维矩形, 单精度.
 */
class Rect2
{
public:
	Vector2 origin;
	Size2   size;

	/**
	 * @brief 默认构造函数.
	 */
	Rect2() = default;

	/**
	 * @brief 构造函数.
	 * 
	 * @param origin 坐标.
	 * @param size   大小.
	 */
	Rect2(const Point2& origin, Size2 size);

	/**
	 * @brief 构造函数.
	 * 
	 * @param x      x坐标.
	 * @param y      y坐标.
	 * @param width  宽.
	 * @param height 高.
	 */
	Rect2(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point2 tl() const;
	Point2 tr() const;
	Point2 bl() const;
	Point2 br() const;

	bool containsPoint(const Point2& point) const;
	bool intersectsRect(const Rect2& rect) const;
};

using Rect2 = Rect2;

/**
 * end of Math group
 * @}
 */
