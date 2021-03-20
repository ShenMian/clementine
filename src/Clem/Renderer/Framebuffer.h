// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include "Clem/Math/Vec2.h"
#include "Clem/Platform.h"
#include "Sprite.h"
#include <vector>

class Rect;

#ifdef OS_UNIX
typedef Tile buffer_t;
#endif

#ifdef OS_WIN
typedef CHAR_INFO buffer_t;
#endif

class Framebuffer
{
public:
	void render();

	void drawSprite(const Point& positon, const Sprite& sprite);

	/**
	 * @brief 绘制点.
	 * 
	 * @param x    x坐标.
	 * @param y    y坐标.
	 * @param tile 瓦片.
	 */
	void drawPoint(int x, int y, const Tile& tile);

	/**
	 * @brief 绘制点.
	 * 
	 * @param p    点的坐标.
	 * @param tile 瓦片.
	 */
	void drawPoint(const Point& p, const Tile& tile);

	/**
	 * @brief 绘制连接两点的直线.
	 * 
	 * @param a    a点坐标.
	 * @param b    b点坐标.
	 * @param tile 瓦片.
	 */
	void drawLine(Point a, Point b, const Tile& tile);

	/**
	 * @brief 绘制矩形.
	 * 
	 * @param r    矩形.
	 * @param tile 瓦片.
	 */
	void drawRect(Rect r, const Tile& tile);

	/**
	 * @brief 绘制实心矩形.
	 * 
	 * @param r    矩形.
	 * @param tile 瓦片.
	 */
	void fillRect(Rect r, const Tile& tile);

	/**
	 * @brief 绘制圆形.
	 * 
	 * @param p      原点坐标.
	 * @param radius 半径.
	 * @param tile   瓦片.
	 */
	void drawCycle(Point p, short radius, const Tile& tile);

	/**
	 * @brief 清除全部绘制内容.
	 */
	void clear();

	void        setSize(const Size&);
	const Size& getSize() const;

private:
	Size                  size;
	std::vector<buffer_t> buffer;
};

#endif // !CLEM_RENDERER_H_
