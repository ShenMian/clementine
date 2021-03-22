// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rect.h"

Rect::Rect(Point origin, Size size)
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

Point Rect::tl() const
{
	return Point(left(), top());
}

Point Rect::tr() const
{
	return Point(right(), top());
}

Point Rect::bl() const
{
	return Point(left(), bottom());
}

Point Rect::br() const
{
	return Point(right(), bottom());
}

bool Rect::containsPoint(const Point& p) const
{
	return top() <= p.y && p.y <= bottom() && left() <= p.x && p.x <= right();
}

bool Rect::intersectsRect(const Rect& r) const
{
	return containsPoint(r.tl()) || containsPoint(r.tr()) ||
				 containsPoint(r.bl()) || containsPoint(r.br());
}
