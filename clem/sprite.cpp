// Copyright 2020 SMS
// License(Apache-2.0)
// Í¼Ïñ

#include "sprite.h"
#include "frame_buffer.h"
#include <assert.h>

void Sprite::drawPoint(Point p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	buffer[(int)p.x + (int)p.y * size.x] = t;
}

void Sprite::drawLine(Point a, Point b, const Tile& t)
{
	auto xDis   = b.x - a.x + 1;
	auto yDis   = b.y - a.y + 1;
	auto maxDis = max(abs(xDis), abs(yDis));

	float xDelta = xDis / maxDis;
	float yDelta = yDis / maxDis;

	float x = a.x, y = a.y;
	for(short i = 0; i < maxDis; i++)
	{
		drawPoint(Point(x, y), t);
		x += xDelta, y += yDelta;
	}
}

void Sprite::drawRect(Rect r, const Tile& t)
{
	for(int x = r.left(); x <= r.right(); x++)
	{
		drawPoint(Point(x, r.top()), t);
		drawPoint(Point(x, r.bottom()), t);
	}
	for(int y = r.top(); y <= r.bottom(); y++)
	{
		drawPoint(Point(r.left(), y), t);
		drawPoint(Point(r.right(), y), t);
	}
}

void Sprite::drawRectFill(Rect r, const Tile& t)
{
	for(int y = 0; y < r.height; y++)
		for(int x = 0; x < r.width; x++)
			drawPoint({r.x + x, r.y + y}, t);
}

void Sprite::setSize(Size s)
{
	size = s;
	buffer.resize(s.area());
}

Size Sprite::getSize() const
{
	return size;
}

void Sprite::onAdd()
{
	auto scene = owner->getScene();
	assert(scene);
	scene->addSprite(*this);
}

void Sprite::onRemove()
{
	auto scene = owner->getScene();
	assert(scene);
	scene->removeSprite(*this);
}
