// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_RECT_H_
#define CLEM_MATH_RECT_H_

#include "../Vector2.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维矩形, 单精度.
 */
class Rect
{
public:
	Vector2 origin;
	Size2   size;

	Rect() = default;
	Rect(const Point2& origin, Size2 size);
	Rect(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point2 tl() const;
	Point2 tr() const;
	Point2 bl() const;
	Point2 br() const;

	bool containsPoint(const Point2& point) const;
	bool intersectsRect(const Rect& rect) const;
};

/**
 * end of Math group
 * @}
 */

#endif // !CLEM_MATH_RECT_H_
