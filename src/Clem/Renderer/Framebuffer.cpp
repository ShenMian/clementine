// Copyright 2021 SMS
// License(Apache-2.0)

#include "Framebuffer.h"
#include "Clem/Math/Rect.h"
#include "Clem/Profiler.h"
#include <cmath>

void Framebuffer::drawSprite(const Point& p, const Sprite& s)
{
	const auto& siz = s.getSize();
	for(int y = 0; y < siz.y; y++)
		for(int x = 0; x < siz.x; x++)
			drawPoint(p.x + x, p.y + y, s.getTile(x, y));
}

void Framebuffer::drawPoint(int x, int y, const Tile& t)
{
	drawPoint({(float)x, (float)y}, t);
}

void Framebuffer::drawLine(Point a, Point b, const Tile& t)
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

void Framebuffer::drawRect(Rect r, const Tile& t)
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

void Framebuffer::fillRect(Rect r, const Tile& t)
{
	for(int y = 0; y < r.size.y; y++)
		for(int x = 0; x < r.size.x; x++)
			drawPoint(r.origin.x + x, r.origin.y + y, t);
}

void Framebuffer::drawCycle(Point c, short r, const Tile& t)
{
	for(int x = 0; x <= r; x++)
	{
		int y = (int)std::sqrt(r * r - x * x);
		drawPoint(c.x + x, c.y + y, t);
		drawPoint(c.x - x, c.y + y, t);
		drawPoint(c.x - x, c.y - y, t);
		drawPoint(c.x + x, c.y - y, t);
	}
	for(int y = 0; y <= r; y++)
	{
		int x = (int)std::sqrt(r * r - y * y);
		drawPoint(c.x + x, c.y + y, t);
		drawPoint(c.x - x, c.y + y, t);
		drawPoint(c.x - x, c.y - y, t);
		drawPoint(c.x + x, c.y - y, t);
	}
}

void Framebuffer::drawString(const Point& pos, std::wstring str)
{
	for(int i = 0; i < str.size(); i++)
		drawPoint(pos.x + i, pos.y, Tile(str[i]));
}

void Framebuffer::clear(const Tile& t)
{
	fillRect(Rect({0, 0}, size), t);
}

void Framebuffer::setSize(const Size& s)
{
	size = s;
	buffer.resize((size_t)s.area());
}

const Size& Framebuffer::getSize() const
{
	return size;
}

#ifdef OS_UNIX

void Framebuffer::drawPoint(const Point& p, const Tile& t)
{
	if(0 <= p.x && p.x < size.x && 0 < p.y && p.y < size.y)
		return;
	buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x] = t;
}

void Framebuffer::output()
{
	PROFILE_FUNC();
}

#endif

#ifdef OS_WIN

void Framebuffer::drawPoint(const Point& p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	auto& buf            = buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x];
	buf.Char.UnicodeChar = t.ch;
	buf.Attributes       = t.color.fore | t.color.back | FOREGROUND_INTENSITY;
}

void Framebuffer::output()
{
	PROFILE_FUNC();

	const auto hOut        = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT writeRegion = {0, 0, (SHORT)size.x, (SHORT)size.y};
	WriteConsoleOutput(hOut, (CHAR_INFO*)buffer.data(), {(SHORT)size.x, (SHORT)size.y}, {0, 0}, &writeRegion);
}

#endif
