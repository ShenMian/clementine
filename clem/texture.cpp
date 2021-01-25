// Copyright 2020 SMS
// License(Apache-2.0)
// 材质

#include "texture.h"
#include <cassert>
#include <math.h>

Texture::Texture()
		: Texture(Size(0, 0))
{
}

Texture::Texture(Size s)
		: Texture(s, Tile())
{
}

Texture::Texture(const Tile& t)
{
	setSize(Size(1, 1));
	tiles[0] = t;
}

Texture::Texture(Size s, const Tile& t)
{
	setSize(s);
	for(ushort i = 0; i < size.area(); i++)
		tiles[i] = t;
}

void Texture::drawTile(const Tile& t, const Point& p)
{
	assert(0 <= p.x && p.x <= size.x && 0 <= p.y && p.y <= size.y);
	tiles[p.x + p.y * size.x] = t;
}

void Texture::drawTexture(const Texture& t, const Point& p)
{
	const auto size = t.getSize();
	for(ushort x = 0; x < size.x; x++)
		for(ushort y = 0; y < size.y; y++)
			drawTile(t.at(x, y), Point(p.x + x, p.y + y));
}

void Texture::drawRect(const Rect& rect, const Tile& t)
{
	for(float i = 0; i < rect.width; i++)
	{
		drawTile(t, Point(rect.x + i, rect.y));
		drawTile(t, Point(rect.x + i, rect.bottom()));
	}
	for(float i = 0; i < rect.height; i++)
	{
		drawTile(t, Point(rect.x, rect.y + i));
		drawTile(t, Point(rect.x, rect.right() + i));
	}
}

void Texture::drawCycle(const Point& c, ushort r, const Tile& t)
{
	for(ushort x = 0; x <= r; x++)
	{
		ushort y = sqrt(r*r - x*x);
		drawTile(t, Point(c.x + x, c.y + y));
		drawTile(t, Point(c.x - x, c.y + y));
		drawTile(t, Point(c.x - x, c.y - y));
		drawTile(t, Point(c.x + x, c.y - y));
	}
	for(ushort y = 0; y <= r; y++)
	{
		ushort x = sqrt(r * r - y * y);
		drawTile(t, Point(c.x + x, c.y + y));
		drawTile(t, Point(c.x - x, c.y + y));
		drawTile(t, Point(c.x - x, c.y - y));
		drawTile(t, Point(c.x + x, c.y - y));
	}
}

const Size& Texture::getSize() const
{
	return size;
}

void Texture::setSize(Size s)
{
	size = s;
	tiles.resize(size.area());
}

void Texture::clear()
{
	for(ushort i = 0; i < size.area(); i++)
		tiles[i] = Tile();
}

const Tile& Texture::at(ushort x, ushort y) const
{
	assert(x < size.x && y < size.y);
	return tiles[x + y * size.x];
}

const Tile& Texture::at(const Point& p) const
{
	return at(p.x, p.y);
}

const Tile& Texture::operator[](const Point& p) const
{
	return at(p);
}

