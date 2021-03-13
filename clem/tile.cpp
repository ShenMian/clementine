// Copyright 2021 SMS
// License(Apache-2.0)

#include "tile.h"
#include <stdio.h>
#include <clem/color.h>

using std::string;

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

void Tile::setChar(char c)
{
	ch = c;
}

char Tile::getChar() const
{
	return ch;
}

void Tile::setColor(const Color& c)
{
	color = c;
}

const Color& Tile::getColor() const
{
	return color;
}

