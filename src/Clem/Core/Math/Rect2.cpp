// Copyright 2021 SMS
// License(Apache-2.0)

#include "Rect2.h"

Rect2::Rect2(const Point2& o, const Size2& s)
		: origin(o), size(s)
{
}

Rect2::Rect2(float x, float y, float w, float h)
		: origin(x, y), size(w, h)
{
}

float Rect2::top() const
{
	return origin.y;
}

float Rect2::bottom() const
{
	return origin.y + size.y;
}

float Rect2::left() const
{
	return origin.x;
}

float Rect2::right() const
{
	return origin.x + size.x;
}

Point2 Rect2::tl() const
{
	return Point2(left(), top());
}

Point2 Rect2::tr() const
{
	return Point2(right(), top());
}

Point2 Rect2::bl() const
{
	return Point2(left(), bottom());
}

Point2 Rect2::br() const
{
	return Point2(right(), bottom());
}

bool Rect2::intersectsPoint(const Point2& p) const
{
	return top() <= p.y && p.y <= bottom() && left() <= p.x && p.x <= right();
}

bool Rect2::intersectsRect(const Rect2& r) const
{
	return std::abs(origin.x - r.origin.x) <= (size.x + r.size.x) / 2 &&
				 std::abs(origin.y - r.origin.y) <= (size.y + r.size.y) / 2;
	// return intersectsPoint(r.tl()) || intersectsPoint(r.tr()) ||
	//			  intersectsPoint(r.bl()) || intersectsPoint(r.br());
}

bool Rect2::isValid() const
{
	return origin.area() >= 0 && size.area() >= 0;
}