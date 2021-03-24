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

	Rect2f() = default;
	Rect2f(const Point2f& origin, Size2f size);
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

Rect2f::Rect2f(const Point2f& o, Size2f s)
		: origin(o), size(s)
{
}

Rect2f::Rect2f(float x, float y, float width, float height)
		: origin(x, y), size(width, height)
{
}

float Rect2f::top() const
{
	return origin.y;
}

float Rect2f::bottom() const
{
	return origin.y + size.y;
}

float Rect2f::left() const
{
	return origin.x;
}

float Rect2f::right() const
{
	return origin.x + size.x;
}

Point2f Rect2f::tl() const
{
	return Point2f(left(), top());
}

Point2f Rect2f::tr() const
{
	return Point2f(right(), top());
}

Point2f Rect2f::bl() const
{
	return Point2f(left(), bottom());
}

Point2f Rect2f::br() const
{
	return Point2f(right(), bottom());
}

bool Rect2f::containsPoint(const Point2f& p) const
{
	return top() <= p.y && p.y <= bottom() && left() <= p.x && p.x <= right();
}

bool Rect2f::intersectsRect(const Rect2f& r) const
{
	return containsPoint(r.tl()) || containsPoint(r.tr()) ||
				 containsPoint(r.bl()) || containsPoint(r.br());
}

/**
 * end of Math group
 * @}
 */
