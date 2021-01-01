// Copyright 2020 SMS
// License(Apache-2.0)
// 大小

#include "size.h"
#include <cassert>

Size::Size()
		: Size(0, 0)
{
}

Size::Size(int x, int y)
		: x(x), y(y)
{
	assert(x >= 0 && y >= 0);
}

ushort Size::area() const
{
	return x * y;
}

Size Size::operator+(const Size& size) const
{
	return Size(x + size.x, y + size.y);
}

