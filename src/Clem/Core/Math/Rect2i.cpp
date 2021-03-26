// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rect2i.h"

Rect2i::Rect2i(const Point2i& o, Size2i s)
		: origin(o), size(s)
{
}

Rect2i::Rect2i(int x, int y, int w, int h)
		: origin(x, y), size(w, h)
{
}

int Rect2i::top() const
{
	return origin.y;
}

int Rect2i::bottom() const
{
	return origin.y + size.y;
}

int Rect2i::left() const
{
	return origin.x;
}

int Rect2i::right() const
{
	return origin.x + size.x;
}

Point2i Rect2i::tl() const
{
	return Point2i(left(), top());
}

Point2i Rect2i::tr() const
{
	return Point2i(right(), top());
}

Point2i Rect2i::bl() const
{
	return Point2i(left(), bottom());
}

Point2i Rect2i::br() const
{
	return Point2i(right(), bottom());
}

bool Rect2i::containsPoint(const Point2i& p) const
{
	return top() <= p.y && p.y <= bottom() && left() <= p.x && p.x <= right();
}

bool Rect2i::intersectsRect(const Rect2i& r) const
{
	return containsPoint(r.tl()) || containsPoint(r.tr()) ||
				 containsPoint(r.bl()) || containsPoint(r.br());
}
