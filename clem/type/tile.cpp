// Copyright 2020 SMS
// License(Apache-2.0)

#include "tile.h"

void Tile::put() const
{
	attr.putc(ch);
}

Tile::Tile()
		: Tile(' ', Attribute())
{
}

Tile::Tile(char ch, const Attribute& attr)
		: ch(ch), attr(attr)
{
}
