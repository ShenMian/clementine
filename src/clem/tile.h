// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_TYPE_TILE_H_
#define CLEM_TYPE_TILE_H_

#include <clem/color.h>

/// 瓦片
class Tile
{
public:
	Tile();
	Tile(char ch);
	Tile(char ch, const Color& color);

	void setChar(char ch);
	char getChar() const;

	void         setColor(const Color& color);
	const Color& getColor() const;

private:
	char  ch;
	Color color;
};

#endif // CLEM_TYPE_TILE_H_
