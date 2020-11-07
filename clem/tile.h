// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_TYPE_TILE_H_
#define CLEM_TYPE_TILE_H_

#include <clem/color.h>

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

	std::string getString() const;

private:
	char  ch;
	Color color;
};

#endif // CLEM_TYPE_TILE_H_
