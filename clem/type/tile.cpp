// Copyright 2020 SMS
// License(Apache-2.0)

#include "tile.h"
#include <stdio.h>
#include <clem/color.h>

void Tile::print() const
{
	color.on();
	putchar(ch);
}

Tile::Tile()
		: Tile(' ')
{
}

Tile::Tile(char c)
	: Tile(c, Color())
{
}

Tile::Tile(char c, const Color& co)
		: ch(c), color(co)
{
}

