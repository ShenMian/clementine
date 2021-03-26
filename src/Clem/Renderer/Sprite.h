// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_SPRITE_H_
#define CLEM_RENDERER_SPRITE_H_

#include "Clem/Component/Component.h"
#include "Clem/Core/Math/Rect2i.h"
#include "Clem/Core/Math/Vector2.h"
#include "Tile.h"
#include <filesystem>
#include <vector>

/**
 * @brief Tile的集合.
 */
class Sprite : public Component
{
public:
	Sprite()              = default;
	Sprite(const Sprite&) = default;
	explicit Sprite(const Size2i& size);

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
	void drawPoint(Point2i p, const Tile& t);

	/**
	 * @brief 绘制连接两点的直线.
	 *
	 * @param a a点坐标.
	 * @param b b点坐标.
	 * @param t 瓦片.
	 */
	void drawLine(Point2i a, Point2i b, const Tile& t);

	/**
	 * @brief 绘制矩形.
	 *
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void drawRect(Rect2i r, const Tile& t);

	/**
	 * @brief 绘制实心矩形.
	 *
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void fillRect(Rect2i r, const Tile& t);

	/**
	 * @brief 绘制圆形.
	 *
	 * @param p 原点坐标.
	 * @param radius 半径.
	 * @param t 瓦片.
	 */
	void drawCycle(Point2i p, short radius, const Tile& t);

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

	const Tile& getTile(int x, int y) const;

	const Tile& getTile(const Point2i&) const;

	/**
	 * @brief 设置可绘制区域的大小
	 */
	void setSize(const Size2i& s);

	/**
	 * @brief 获取可绘制区域的大小
	 */
	const Size2i& getSize() const;

	// void load(const std::filesystem::path& path);
	// void store(const std::filesystem::path& path) const;

	Sprite& operator=(const Sprite&) = default;

private:
	Size2i            size;
	std::vector<Tile> buffer;
};

#endif // !CLEM_RENDERER_SPRITE_H_
