// Copyright 2021 SMS
// License(Apache-2.0)

#include "Framebuffer.h"
#include "Clem/Profiler.h"
#include "Color.h"
#include "Cursor.h"
#include <cassert>
#include <cmath>

namespace clem
{
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

void Framebuffer::drawLine(const Point2i& start, const Point2i& end, const Tile& t)
{
	const float dx  = (float)end.x - start.x;
	const float dy  = (float)end.y - start.y;
	const float max = std::max(dx, dy);
	const float kx  = max / dx;
	const float ky  = max / dy;

	float x = (float)start.x, y = (float)start.y;
	for(int i = 0; i <= max; i++)
	{
		drawPoint((int)(x + 0.5f), (int)(y + 0.5f), t);
		x += kx, y += ky;
	}
}

void Framebuffer::drawRect(const Rect2i& r, const Tile& t)
{
	for(int x = 0; x < r.size.x; x++)
	{
		drawPoint(r.origin.x + x, r.top(), t);
		drawPoint(r.origin.x + x, r.bottom(), t);
	}
	for(int y = 0; y < r.size.y; y++)
	{
		drawPoint(r.left(), r.origin.y + y, t);
		drawPoint(r.right(), r.origin.y + y, t);
	}
}

void Framebuffer::fillRect(const Rect2i& r, const Tile& t)
{
	for(int y = 0; y < r.size.y; y++)
		for(int x = 0; x < r.size.x; x++)
			drawPoint(r.origin.x + x, r.origin.y + y, t);
}

void Framebuffer::drawCycle(const Point2i& c, short r, const Tile& t)
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

void Framebuffer::drawString(const Point2i& pos, std::wstring str, Color c)
{
	for(int i = 0; i < str.size(); i++)
		drawPoint(pos.x + i, pos.y, Tile(str[i], c));
}

void Framebuffer::clear(const Tile& t)
{
	fillRect(Rect2i({0, 0}, size), t);
}

void Framebuffer::setSize(const Size2i& s)
{
	size = s;
	buffer.resize((size_t)s.area());
}

const Size2i& Framebuffer::getSize() const
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

void setForeColor(uint8_t fore)
{
	switch(fore)
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
		assert(false);
	}
}

void setBackColor(uint8_t back)
{
	switch(back)
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
		assert(false);
	}
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
			setForeColor(buf.color.fore);
			setBackColor(buf.color.back);
			printf("%C", buf.ch);
		}
	}
	fflush(stdout);
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
} // namespace clem