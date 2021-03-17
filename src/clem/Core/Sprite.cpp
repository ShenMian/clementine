// Copyright 2021 SMS
// License(Apache-2.0)

#include "Sprite.h"
#include "clem/Math/Point.h"
#include "clem/type/rect.h"

void NSprite::drawPoint(int x, int y, const Tile& t)
{
	drawPoint(Point(x, y), t);
}

void NSprite::drawPoint(Point p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	buffer[(int)p.x + (int)p.y * size.x] = t;
}

void NSprite::drawLine(Point a, Point b, const Tile& t)
{
	auto xDis   = b.x - a.x + 1;
	auto yDis   = b.y - a.y + 1;
	auto maxDis = std::max(abs(xDis), abs(yDis));

	float xDelta = xDis / maxDis;
	float yDelta = yDis / maxDis;

	float x = a.x, y = a.y;
	for(int i = 0; i < maxDis; i++)
	{
		drawPoint(x, y, t);
		x += xDelta, y += yDelta;
	}
}

void NSprite::drawRect(Rect r, const Tile& t)
{
	for(int x = r.left(); x <= r.right(); x++)
	{
		drawPoint(x, r.top(), t);
		drawPoint(x, r.bottom(), t);
	}
	for(int y = r.top(); y <= r.bottom(); y++)
	{
		drawPoint(r.left(), y, t);
		drawPoint(r.right(), y, t);
	}
}

void NSprite::fillRect(Rect r, const Tile& t)
{
	for(int y = 0; y < r.height; y++)
		for(int x = 0; x < r.width; x++)
			drawPoint(r.x + x, r.y + y, t);
}

void NSprite::drawCycle(Point c, short r, const Tile& t)
{
	// TODO(SMS): ÓÅ»¯Ëã·¨
	for(int x = 0; x <= r; x++)
	{
		int y = sqrt(r * r - x * x);
		drawPoint(c.x + x, c.y + y, t);
		drawPoint(c.x - x, c.y + y, t);
		drawPoint(c.x - x, c.y - y, t);
		drawPoint(c.x + x, c.y - y, t);
	}
	for(int y = 0; y <= r; y++)
	{
		int x = sqrt(r * r - y * y);
		drawPoint(c.x + x, c.y + y, t);
		drawPoint(c.x - x, c.y + y, t);
		drawPoint(c.x - x, c.y - y, t);
		drawPoint(c.x + x, c.y - y, t);
	}
}

void NSprite::clear()
{
	fillRect(Rect({0, 0}, size), Tile(' '));
}

void NSprite::setSize(const Size& s)
{
	size = s;
	buffer.resize(s.area());
}

const Size& NSprite::getSize() const
{
	return size;
}
