// Copyright 2020 SMS
// License(Apache-2.0)
// 材质

#ifndef CLEM_TEXTURE_H_
#define CLEM_TEXTURE_H_

typedef unsigned short ushort;

#include <vector>
#include <clem/tile.h>
#include <clem/type.h>

class Texture
{
public:
	Texture();
	Texture(const Tile& tile);
	Texture(Size size);
	Texture(Size size, const Tile& tile);

	void drawPoint(const Point& pos, const Tile& tile);
	void drawTexture(const Texture& texture, const Point& pos);
	void drawRect(const Rect& rect, const Tile& t);
	void drawCycle(const Point& center, ushort radius, const Tile& t);

	const Tile& at(const Point& pos) const;
	const Tile& at(ushort x, ushort y) const;
	const Tile& operator[](const Point& pos) const;

	const Size& getSize() const;
	void        setSize(Size size);
	void        clear();

private:
	Size              size;
	std::vector<Tile> tiles;
};

#endif // CLEM_TEXTURE_H_
