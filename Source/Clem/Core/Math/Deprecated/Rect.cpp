// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rect.h"

Rect::Rect(const Point2& origin, Size2 size)
		: origin(origin), size(size)
{
}

Rect::Rect(float x, float y, float width, float height)
		: origin(x, y), size(width, height)
{
}

float Rect::top() const
{
	return origin.y;
}

float Rect::bottom() const
{
	return origin.y + size.y;
}

float Rect::left() const
{
	return origin.x;
}

float Rect::right() const
{
	return origin.x + size.x;
}

Point2 Rect::tl() const
{
	return Point2(left(), top());
}

Point2 Rect::tr() const
{
	return Point2(right(), top());
}

Point2 Rect::bl() const
{
	return Point2(left(), bottom());
}

Point2 Rect::br() const
{
	return Point2(right(), bottom());
}

bool Rect::containsPoint(const Point2& p) const
{
	return top() <= p.y && p.y <= bottom() && left() <= p.x && p.x <= right();
}

bool Rect::intersectsRect(const Rect& r) const
{
	return containsPoint(r.tl()) || containsPoint(r.tr()) ||
				 containsPoint(r.bl()) || containsPoint(r.br());
}