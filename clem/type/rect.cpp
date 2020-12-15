// Copyright 2020 SMS
// License(Apache-2.0)
// 矩形

#include "rect.h"
#include "size.h"
#include "point.h"
#include "vector.h"

Rect::Rect()
		: Rect(0, 0, 0, 0)
{
}

Rect::Rect(const Vector& vec, const Size& size)
		: Rect(vec.x, vec.y, size.x, size.y)
{
}

Rect::Rect(ushort x, ushort y, ushort width, ushort height)
		: x(x), y(y), width(width), height(height)
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
