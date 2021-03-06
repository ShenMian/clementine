// Copyright 2020 SMS
// License(Apache-2.0)
// ºÐÐÎÅö×²Ìå

#include "shape_box.h"

PhysicsShapeBox(float x, float y, float w, float h)
		: x(x), y(y), width(w), height(h)
{
}

float Rect::top() const
{
	return y;
}

float Rect::bottom() const
{
	return y - height;
}

float Rect::left() const
{
	return x;
}

float Rect::right() const
{
	return x + width;
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

Point Rect::center() const
{
	return Point(x + width / 2, y - height / 2);
}

Size Rect::size() const
{
	return Size(width, height);
}
