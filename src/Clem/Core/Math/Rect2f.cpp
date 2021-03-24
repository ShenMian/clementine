// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rect2f.h"

Rect2f::Rect2f(const Point2f& o, Size2f s)
		: origin(o), size(s)
{
}

Rect2f::Rect2f(float x, float y, float w, float h)
		: origin(x, y), size(w, h)
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
