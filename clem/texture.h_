// Copyright 2020 SMS
// License(Apache-2.0)
// 材质

#ifndef CLEM_TEXTURE_H_
#define CLEM_TEXTURE_H_

typedef unsigned short ushort;

#include <vector>
#include "type.h"

class Tile;
class Rect;
class Point;

class Texture
{
public:
	Texture();
	Texture(Size size);
	Texture(const Tile& tile);
	Texture(Size size, const Tile& tile);

	void draw(const Tile& tile, const Point& pos);
	void draw(const Texture& texture, const Point& pos);
	void drawRect(const Tile& tile, const Rect& rect);
	void drawCycle(const Tile& tile, ushort radius, Point center);

	const Tile& operator[](const Point& pos) const;

	const Size& getSize() const;
	void        setSize(Size size);
	void        clear();

private:
	Size              size;
	std::vector<Tile> tiles;
};

#endif // CLEM_TEXTURE_H_
