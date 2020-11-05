// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_TYPE_TILE_H_
#define CLEM_TYPE_TILE_H_

#include <clem/color.h>

class Tile
{
public:
	char  ch;
	Color color;

	void print() const;

	Tile();
	Tile(char ch);
	Tile(char ch, const Color& attr);
};

#endif // CLEM_TYPE_TILE_H_
