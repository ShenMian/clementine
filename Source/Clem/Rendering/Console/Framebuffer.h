// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Rect2.h"
#include "Clem/Core/Math/Vector2i.h"
#include "Clem/Platform.h"
#include "Sprite.h"
#include <vector>

namespace clem
{
#ifdef OS_UNIX
typedef Tile buffer_t;
#endif

#ifdef OS_WIN
typedef CHAR_INFO buffer_t;
#endif

/**
 * @brief 帧缓冲区.
 */
class Framebuffer
{
public:
	void output();

	void drawSprite(const Point2i& positon, const Sprite& sprite);

	/**
	 * @brief 绘制点.
	 *
	 * @param x x坐标.
	 * @param y y坐标.
	 * @param t 瓦片.
	 */
	void drawPoint(int x, int y, const Tile& t);

	/**
	 * @brief 绘制点.
	 *
	 * @param p 点的坐标.
	 * @param t 瓦片.
	 */
	void drawPoint(const Point2i& p, const Tile& t);

	/**
	 * @brief 绘制连接两点的线段.
	 *
	 * @param a 线段端点坐标.
	 * @param b 线段另一端点坐标.
	 * @param t 瓦片.
	 */
	void drawLine(const Point2i& start, const Point2i& end, const Tile& t);

	/**
	 * @brief 绘制矩形.
	 *
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void drawRect(const Rect2i& r, const Tile& t);

	/**
	 * @brief 绘制实心矩形.
	 *
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void fillRect(const Rect2i& r, const Tile& t);

	/**
	 * @brief 绘制圆形.
	 *
	 * @param p 原点坐标.
	 * @param radius 半径.
	 * @param t 瓦片.
	 */
	void drawCycle(const Point2i& p, short radius, const Tile& t);

	/**
	 * @brief 绘制字符串.
	 *
	 * @param pos   绘制起点的位置
	 * @param str   要绘制的字符串
	 * @param color 顔色
	 */
	void drawString(const Point2i& pos, std::wstring str, Color color = Color());

	/**
	 * @brief 清除全部绘制内容.
	 */
	void clear(const Tile& = Tile::blank);

	void          setSize(const Size2i&);
	const Size2i& getSize() const;

private:
	Size2i                size;
	std::vector<buffer_t> buffer;
};
} // namespace clem
