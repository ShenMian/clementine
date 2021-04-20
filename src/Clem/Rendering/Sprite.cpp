// Copyright 2021 SMS
// License(Apache-2.0)

#include "Sprite.h"
#include "Clem/Core/Math/Rect2i.h"
#include "Clem/Logger.h"
#include <cmath>
#include <fstream>

using namespace std::filesystem;

namespace clem
{
Sprite::Sprite(const Size2i& size)
{
	setSize(size);
}

void Sprite::drawPoint(int x, int y, const Tile& t)
{
	if(size.area() == 0)
	{
		CLEM_LOG_WARN("core", "try to draw something when the sprite size is zero");
		assert(false); // TODO: debug 用
	}
	drawPoint({x, y}, t);
}

void Sprite::drawPoint(const Point2i& p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y /*|| t.ch == '\0'*/)
		return;
	buffer[p.x + p.y * size.x] = t;
}

void Sprite::drawLine(const Point2i& a, const Point2i& b, const Tile& t)
{
	auto xDis   = b.x - a.x + 1;
	auto yDis   = b.y - a.y + 1;
	auto maxDis = std::max(abs(xDis), abs(yDis));

	float xDelta = (float)xDis / maxDis;
	float yDelta = (float)yDis / maxDis;

	float x = (float)a.x, y = (float)a.y;
	for(int i = 0; i < maxDis; i++)
	{
		drawPoint((int)x, (int)y, t);
		x += xDelta, y += yDelta;
	}
}

void Sprite::drawRect(const Rect2i& r, const Tile& t)
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

void Sprite::fillRect(const Rect2i& r, const Tile& t)
{
	for(int y = 0; y < r.size.y; y++)
		for(int x = 0; x < r.size.x; x++)
			drawPoint(r.origin.x + x, r.origin.y + y, t);
}

void Sprite::drawCycle(const Point2i& c, short r, const Tile& t)
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

void Sprite::drawString(const Point2i& pos, std::wstring_view str, Color c)
{
	const auto& size = getSize();
	int         x = 0, y = 0;
	for(auto ch : str)
	{
		if(ch == '\n' || y == size.y)
		{
			x = 0;
			y++;
		}
		else if(ch == '\r')
			x = 0;
		else
		{
			drawPoint({pos.x + x, pos.y + y}, Tile(ch, c));
			x++;
		}
	}
	//for(int i = 0; i < str.size(); i++)
	//	drawPoint(pos.x + i, pos.y, Tile(str[i], c));
}

void Sprite::clear(const Tile& t)
{
	fillRect(Rect2i({0, 0}, size), t);
}

const Tile& Sprite::getTile(int x, int y) const
{
	return getTile({x, y});
}

const Tile& Sprite::getTile(const Point2i& p) const
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return Tile::blank;
	return buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x];
}

void Sprite::setSize(const Size2i& s)
{
	size = s;
	buffer.resize(s.area());
}

const Size2i& Sprite::getSize() const
{
	return size;
}

void Sprite::setDepth(size_t d)
{
	depth = d;
}

size_t Sprite::getDepth() const
{
	return depth;
}

} // namespace clem

/*
void Sprite::load(const path& path)
{
	if(!exists(path))
		CLEM_CORE_CRITICAL("file doesn't exists" + path.string());
	std::wifstream file(absolute(path), std::ios::binary);
	file.read((wchar_t*)&size, sizeof(size));
	auto buf = new wchar_t[size.height];
	for(int i = 0; i < size.height; i++)
	{
		file.read((char*)buf, size.height * sizeof(wchar_t));
		drawString({0, (float)i}, buf);
	}
}

void Sprite::store(const path& path) const
{
	if(!exists(path))
		CLEM_CORE_CRITICAL("file doesn't exists" + path.string());
	std::wofstream file(absolute(path), std::ios::binary);
	file.write((wchar_t*)&size, sizeof(size));
}
*/