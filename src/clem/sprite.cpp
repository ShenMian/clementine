// Copyright 2021 SMS
// License(Apache-2.0)
// 图像

#include "sprite.h"
#include "frame_buffer.h"
#include <assert.h>

/**
 * @brief 绘制点
 * 
 * @param p 点的坐标
 * @param t 瓦片
 */
void Sprite::drawPoint(Point p, const Tile& t)
{
	if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
		return;
	buffer[(int)p.x + (int)p.y * size.x] = t;
}

/**
 * @brief 绘制直线
 * 
 * @param a 点A
 * @param b 点B
 * @param t 瓦片
 */
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
		drawPoint(Point(x, y), t);
		x += xDelta, y += yDelta;
	}
}

/**
 * @brief 绘制矩形
 * 
 * @param r 矩形
 * @param t 瓦片
 */
void Sprite::drawRect(Rect r, const Tile& t)
{
	// TODO(SMS): 优化算法
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

/**
 * @brief 绘制实心矩形
 * 
 * @param r 矩形
 * @param t 瓦片
 */
void Sprite::fillRect(Rect r, const Tile& t)
{
	for(int y = 0; y < r.height; y++)
		for(int x = 0; x < r.width; x++)
			drawPoint({r.x + x, r.y + y}, t);
}

/**
 * @brief 绘制圆
 * 
 * @param c 圆心坐标
 * @param r 半径
 * @param t 瓦片
 */
void Sprite::drawCycle(Point c, short r, const Tile& t)
{
	for(int x = 0; x <= r; x++)
	{
		int y = sqrt(r * r - x * x);
		drawPoint(Point(c.x + x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y - y), t);
		drawPoint(Point(c.x + x, c.y - y), t);
	}
	for(int y = 0; y <= r; y++)
	{
		int x = sqrt(r * r - y * y);
		drawPoint(Point(c.x + x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y + y), t);
		drawPoint(Point(c.x - x, c.y - y), t);
		drawPoint(Point(c.x + x, c.y - y), t);
	}
}

void Sprite::clear()
{
	fillRect(Rect({0, 0}, size), Tile(' '));
}

/**
 * @brief 设置可绘制区域的大小
 * 
 * @param s 
 */
void Sprite::setSize(Size s)
{
	size = s;
	buffer.resize(s.area());
}

/**
 * @brief 获取可绘制区域的大小
 * 
 * @return Size 
 */
Size Sprite::getSize() const
{
	return size;
}

void Sprite::onAdd()
{
	auto scene = owner->getScene();
	assert(scene != nullptr);
	scene->addSprite(*this);
}

void Sprite::onRemove()
{
	auto scene = owner->getScene();
	assert(scene != nullptr);
	scene->removeSprite(*this);
}
