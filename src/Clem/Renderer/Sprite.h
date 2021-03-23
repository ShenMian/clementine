// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_SPRITE_H_
#define CLEM_RENDERER_SPRITE_H_

#include "Clem/Component/Component.h"
#include "Clem/Math/Vec2.h"
#include "Tile.h"
#include <filesystem>
#include <vector>

class Rect;

/**
 * @brief Tile的集合.
 */
class Sprite : public Component
{
public:
	Sprite()              = default;
	Sprite(const Sprite&) = default;
	Sprite& operator=(const Sprite&) = default;
	explicit Sprite(const Size& size);

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
	void drawPoint(Point p, const Tile& t);

	/**
	 * @brief 绘制连接两点的直线.
	 * 
	 * @param a a点坐标.
	 * @param b b点坐标.
	 * @param t 瓦片.
	 */
	void drawLine(Point a, Point b, const Tile& t);

	/**
	 * @brief 绘制矩形.
	 * 
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void drawRect(Rect r, const Tile& t);

	/**
	 * @brief 绘制实心矩形.
	 * 
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void fillRect(Rect r, const Tile& t);

	/**
	 * @brief 绘制圆形.
	 * 
	 * @param p 原点坐标.
	 * @param radius 半径.
	 * @param t 瓦片.
	 */
	void drawCycle(Point p, short radius, const Tile& t);

	/**
	 * @brief 绘制字符串.
	 * 
	 * @param pos   绘制起点的位置
	 * @param str   要绘制的字符串
	 * @param color 顔色
	 */
	void drawString(const Point& pos, std::wstring str, Color color = Color());

	/**
	 * @brief 清除全部绘制内容.
	 */
	void clear();

	const Tile& getTile(int x, int y) const;

	const Tile& getTile(const Point&) const;

	/**
	 * @brief 设置可绘制区域的大小
	 */
	void setSize(const Size& s);

	/**
	 * @brief 获取可绘制区域的大小
	 */
	const Size& getSize() const;

	// void load(const std::filesystem::path& path);
	// void store(const std::filesystem::path& path) const;

private:
	Size              size;
	std::vector<Tile> buffer;
};

#endif // !CLEM_RENDERER_SPRITE_H_
