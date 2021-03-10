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

float Rect::top() const
{
  return y;
}

float Rect::bottom() const
{
	return y + height - 1;
}

float Rect::left() const
{
  return x;
}

float Rect::right() const
{
	return x + width - 1;
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

Point Rect::position() const
{
  return Point(x, y);
}

Point Rect::center() const
{
	return Point(x + width/2, y - height/2);
}

Size Rect::size() const
{
	return Size(width, height);
}

float Rect::area() const
{
  return width * height;
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
  if(contains(a.tl()) || contains(a.tr()) || contains(a.bl()) || contains(a.br()))
	  return true;
  else
    return false;
}

