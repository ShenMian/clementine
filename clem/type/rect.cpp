// Copyright 2020 SMS
// License(Apache-2.0)
// 矩形

#include "rect.h"
#include "size.h"
#include "point.h"

Rect::Rect()
		: Rect(0, 0, 0, 0)
{
}

Rect::Rect(const Point& p, const Size& size)
		: Rect(p.x, p.y, size.x, size.y)
{
}

Rect::Rect(float x, float y, float w, float h)
		: x(x), y(y), width(w), height(h)
{
}

float Rect::right() const
{
	return x + width;
}

float Rect::bottom() const
{
	return y - height;
}

Point Rect::center() const
{
	return Point(x + width/2, y - height/2);
}

Size Rect::size() const
{
	return Size(width, height);
}

bool Rect::contains(const Point& a) const
{
	if(x <= a.x && a.x <= right() && y <= a.y && a.y <= bottom())
		return true;
	else
		return false;
}

bool Rect::contains(const Rect& a) const
{
	return true;
}

