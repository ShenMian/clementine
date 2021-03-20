﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Sprite.h"
#include "Clem/Math/Rect.h"
#include <cmath>
#include <fstream>

using namespace std::filesystem;

void Sprite::drawPoint(int x, int y, const Tile& t)
{
	drawPoint({(float)x, (float)y}, t);
}

void Sprite::drawPoint(Point p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x] = t;
}

void Sprite::drawLine(Point a, Point b, const Tile& t)
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

void Sprite::drawRect(Rect r, const Tile& t)
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

void Sprite::fillRect(Rect r, const Tile& t)
{
	for(int y = 0; y < r.size.y; y++)
		for(int x = 0; x < r.size.x; x++)
			drawPoint(r.origin.x + x, r.origin.y + y, t);
}

void Sprite::drawCycle(Point c, short r, const Tile& t)
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

void Sprite::drawString(const Point& pos, std::wstring str)
{
	for(int i = 0; i < str.size(); i++)
		drawPoint(pos.x + i, pos.y, str[i]);
}

void Sprite::clear()
{
	fillRect(Rect({0, 0}, size), Tile::blank);
}

const Tile& Sprite::getTile(int x, int y) const
{
	return getTile(Point(x, y));
}

const Tile& Sprite::getTile(const Point& p) const
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return Tile::blank;
	return buffer[(size_t)p.x + (size_t)p.y * (size_t)size.x];
}

void Sprite::setSize(const Size& s)
{
	size = s;
	buffer.resize((size_t)s.area());
}

const Size& Sprite::getSize() const
{
	return size;
}

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

const Tile Tile::blank;

Tile::Tile(wchar_t ch, short attr)
		: ch(ch), attr(attr)
{
}