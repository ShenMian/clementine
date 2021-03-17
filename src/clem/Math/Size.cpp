// Copyright 2021 SMS
// License(Apache-2.0)

#include "Size.h"
#include <cassert>

Size::Size(short x, short y)
		: x(x), y(y)
{
	assert(x >= 0 && y >= 0);
}

short Size::area() const
{
	return x * y;
}

/*
Size Size::operator+(const Size& s) const
{
	return Size(x + s.x, y + s.y);
}

bool Size::operator==(const Size& s) const
{
	return x == s.x && y == s.y;
}

bool Size::operator!=(const Size& s) const
{
	return !(*this == s);
}
*/
