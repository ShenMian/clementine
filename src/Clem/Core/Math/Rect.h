// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_RECT_H_
#define CLEM_MATH_RECT_H_

#include "Vec2.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief ¶þÎ¬¾ØÐÎ.
 */
class Rect
{
public:
	Vec2<float> origin;
	Size        size;

	Rect() = default;
	Rect(const Point<float>& origin, Size size);
	Rect(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point<float> tl() const;
	Point<float> tr() const;
	Point<float> bl() const;
	Point<float> br() const;

	bool containsPoint(const Point<float>& point) const;
	bool intersectsRect(const Rect& rect) const;
};

/**
 * end of Math group
 * @}
 */

#endif // !CLEM_MATH_RECT_H_
