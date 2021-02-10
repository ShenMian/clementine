// Copyright 2020 SMS
// License(Apache-2.0)
// 材质

#include "texture.h"
#include <cassert>
#include <math.h>
#include "cursor.h"

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

void Texture::drawPoint(const Point& p, const Tile& t)
{
	if(!(0 <= p.x && p.x < size.x && 0 <= p.y && p.y < size.y))
		;

	tiles[p.x + p.y * size.x] = t;
	dirty = true;
}

void Texture::drawLine(Point a, Point b, const Tile& t)
{
	auto  xDis   = b.x - a.x;
	auto  yDis   = b.y - a.y;
	auto  maxDis = std::max(abs(xDis), abs(yDis));

	float xDelta = xDis / maxDis;
	float yDelta = yDis / maxDis;

	float x = a.x, y = a.y;
	for(short i = 1; i <= maxDis; i++)
	{
		drawPoint(Point(x + 0.5, y + 0.5), t);
		x += xDelta, y += yDelta;
	}
}

void Texture::drawRect(const Rect& rect, const Tile& t)
{
	for(float i = 0; i < rect.width; i++)
	{
		drawPoint(Point(rect.x + i, rect.y), t);
		drawPoint(Point(rect.x + i, rect.bottom()), t);
	}
	for(float i = 0; i < rect.height; i++)
	{
		drawPoint(Point(rect.x, rect.y + i), t);
		drawPoint(Point(rect.x, rect.right() + i), t);
	}
}

void Texture::drawCycle(const Point& c, ushort r, const Tile& t)
{
	for(ushort x = 0; x <= r; x++)
	{
		ushort y = sqrt(r*r - x*x);
		drawPoint(Point(c.x + x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y - y), t);
		drawPoint(Point(c.x + x, c.y - y), t);
	}
	for(ushort y = 0; y <= r; y++)
	{
		ushort x = sqrt(r * r - y * y);
		drawPoint(Point(c.x + x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y - y), t);
		drawPoint(Point(c.x + x, c.y - y), t);
	}
}

void Texture::drawTexture(const Texture& t, const Point& p)
{
	const auto size = t.getSize();
	for(ushort x = 0; x < size.x; x++)
		for(ushort y = 0; y < size.y; y++)
			drawPoint(Point(p.x + x, p.y + y), t.at(x, y));
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

const Tile& Texture::at(short x, short y) const
{
	assert(0 <= x && x < size.x && 0 <= y && y < size.y);
	return tiles[x + y * size.x];
}

const Tile& Texture::at(const Point& p) const
{
	return at(p.x, p.y);
}

void Texture::render(Rect& rect)
{
	for(short y = 0; y < size.y; y++)
	{
		Cursor::move(rect.x, rect.y + y);
		for(short x = 0; x < size.x; x++)
			printf("%s", at(x, y).getString().c_str());
	}
}
