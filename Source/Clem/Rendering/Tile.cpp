// Copyright 2021 SMS
// License(Apache-2.0)

#include "Tile.h"

const Tile Tile::blank;

Tile::Tile(wchar_t ch, Color color)
		: ch(ch), color(color)
{
}