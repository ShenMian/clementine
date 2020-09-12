// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_TYPE_TILE_H_
#define CLEM_TYPE_TILE_H_

#include <clem/attribute.h>

class Tile
{
public:
	char      ch;
	Attribute attr;

	void put() const;

	Tile();
	Tile(char ch, const Attribute& attr);
};

#endif // CLEM_TYPE_TILE_H_
