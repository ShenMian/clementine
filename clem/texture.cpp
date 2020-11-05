// Copyright 2020 SMS
// License(Apache-2.0)
// 材质

#include "texture.h"
#include <assert.h>
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
	setSize(Size(1,1));
	tiles[0] = t;
}

Texture::Texture(Size s, const Tile& t)
{
	setSize(s);
	for(int i = 0; i < size.area(); i++)
		tiles[i] = t;
}

void Texture::drawTile(const Tile& t, const Point& p)
{
	tiles[p.x + p.y * size.x] = t;
}

void Texture::drawTexture(const Texture& t, const Point& p)
{
	const auto s = t.getSize();
	for(float x = 0; x < s.x; x++)
		for(float y = 0; y < s.y; y++)
			drawTile(at({x, y}), {p.x + x, p.y + y});
}

void Texture::drawRect(const Rect& rect, const Tile& t)
{
	for(float i = 0; i < rect.width; i++)
	{
		drawTile(t, {rect.x + i, rect.y});
		drawTile(t, {rect.x + i, rect.bottom()});
	}
	for(float i = 0; i < rect.height; i++)
	{
		drawTile(t, {rect.x, rect.y + i});
		drawTile(t, {rect.right(), rect.y + i});
	}
}

void Texture::drawCycle(const Point& c, ushort r, const Tile& t)
{
	for(ushort x = 0; x <= r; x++)
	{
		ushort y = sqrt(r*r - x*x);
		drawTile(t, {c.x + x, c.y + y});
		drawTile(t, {c.x - x, c.y + y});
		drawTile(t, {c.x - x, c.y - y});
		drawTile(t, {c.x + x, c.y - y});
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
	tiles.clear();
	tiles.resize(size.area());
}

const Tile& Texture::at(const Point& p) const
{
	assert(p.x <= size.x && p.y <= size.y);
	return tiles[p.x + p.y * size.x];
}

const Tile& Texture::operator[](const Point& p) const
{
	return at(p);
}

