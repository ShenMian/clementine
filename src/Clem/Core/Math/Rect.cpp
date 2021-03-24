// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rect.h"

Rect::Rect(const Point<float>& origin, Size size)
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

Point<float> Rect::tl() const
{
	return Point<float>(left(), top());
}

Point<float> Rect::tr() const
{
	return Point<float>(right(), top());
}

Point<float> Rect::bl() const
{
	return Point<float>(left(), bottom());
}

Point<float> Rect::br() const
{
	return Point<float>(right(), bottom());
}

bool Rect::containsPoint(const Point<float>& p) const
{
	return top() <= p.y && p.y <= bottom() && left() <= p.x && p.x <= right();
}

bool Rect::intersectsRect(const Rect& r) const
{
	return containsPoint(r.tl()) || containsPoint(r.tr()) ||
				 containsPoint(r.bl()) || containsPoint(r.br());
}
