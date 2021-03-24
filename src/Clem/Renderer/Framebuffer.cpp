// Copyright 2021 SMS
// License(Apache-2.0)

#include "Framebuffer.h"
#include "Clem/Profiler.h"
#include "Color.h"
#include "Cursor.h"
#include <cassert>
#include <cmath>

void Framebuffer::drawSprite(const Point2i& p, const Sprite& s)
{
	const auto& siz = s.getSize();
	for(int y = 0; y < siz.y; y++)
		for(int x = 0; x < siz.x; x++)
			drawPoint(p.x + x, p.y + y, s.getTile(x, y));
}

void Framebuffer::drawPoint(int x, int y, const Tile& t)
{
	drawPoint({x, y}, t);
}

void Framebuffer::drawLine(Point2i a, Point2i b, const Tile& t)
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

void Framebuffer::drawRect(Rect2i r, const Tile& t)
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

void Framebuffer::fillRect(Rect2i r, const Tile& t)
{
	for(int y = 0; y < r.size.y; y++)
		for(int x = 0; x < r.size.x; x++)
			drawPoint(r.origin.x + x, r.origin.y + y, t);
}

void Framebuffer::drawCycle(Point2i c, short r, const Tile& t)
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

void Framebuffer::drawString(const Point2i& pos, std::wstring str)
{
	for(int i = 0; i < str.size(); i++)
		drawPoint(pos.x + i, pos.y, Tile(str[i]));
}

void Framebuffer::clear(const Tile& t)
{
	fillRect(Rect2i({0, 0}, size), t);
}

void Framebuffer::setSize(const Size2& s)
{
	size = s;
	buffer.resize((size_t)s.area());
}

const Size2& Framebuffer::getSize() const
{
	return size;
}

#ifdef OS_UNIX

void Framebuffer::drawPoint(const Point2i& p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x] = t;
}

void Framebuffer::output()
{
	PROFILE_FUNC();

	for(int y = 0; y < size.y; y++)
	{
		Cursor::move(0, y);
		for(int x = 0; x < size.x; x++)
		{
			auto& buf = buffer[x + y * size.x];

			switch(buf.color.fore)
			{
			case Color::black:
				printf("\x1b[30m");
				break;

			case Color::red:
				printf("\x1b[31m");
				break;

			case Color::green:
				printf("\x1b[32m");
				break;

			case Color::yellow:
				printf("\x1b[33m");
				break;

			case Color::blue:
				printf("\x1b[34m");
				break;

			case Color::purple:
				printf("\x1b[35m");
				break;

			case Color::cyan:
				printf("\x1b[36m");
				break;

			case Color::white:
				printf("\x1b[37m");
				break;

			default:
				assert(false); // ��Чǰ����ɫ����
			}

			switch(buf.color.back)
			{
			case Color::black:
				printf("\x1b[40m");
				break;

			case Color::red:
				printf("\x1b[41m");
				break;

			case Color::green:
				printf("\x1b[42m");
				break;

			case Color::yellow:
				printf("\x1b[43m");
				break;

			case Color::blue:
				printf("\x1b[44m");
				break;

			case Color::purple:
				printf("\x1b[45m");
				break;

			case Color::cyan:
				printf("\x1b[46m");
				break;

			case Color::white:
				printf("\x1b[47m");
				break;

			default:
				assert(false); // ��Ч������ɫ����
			}

			printf("%C", buf.ch);
		}
	}
}

#endif

#ifdef OS_WIN

void Framebuffer::drawPoint(const Point2i& p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	auto& buf            = buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x];
	buf.Char.UnicodeChar = t.ch;
	buf.Attributes       = t.color.fore | t.color.back << 4 | FOREGROUND_INTENSITY;
}

void Framebuffer::output()
{
	PROFILE_FUNC();

	const auto hOut        = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT writeRegion = {0, 0, (SHORT)size.x, (SHORT)size.y};
	WriteConsoleOutput(hOut, (CHAR_INFO*)buffer.data(), {(SHORT)size.x, (SHORT)size.y}, {0, 0}, &writeRegion);
}

#endif
