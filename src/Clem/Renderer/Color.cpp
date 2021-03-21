// Copyright 2021 SMS
// License(Apache-2.0)

#include "Color.h"

Color::Color(short color)
{
	fore = color & 0x0F;
	back = color & 0xF0;
}

Color::Color(short f, short b)
		: fore(f), back(b)
{
}
