// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Components/Component.h"
#include "Core/Math/Math.h"
#include "ECS/ECS.h"
#include "Tile.h"
#include <filesystem>
#include <vector>

namespace clem
{

/**
 * @brief 精灵.
 */
class Sprite : public Component
{
	CLEM_DECLARE_TYPE;

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
	void drawString(const Point2i& pos, std::wstring_view str, Color color = Color());

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

	void setDepth(size_t);

	size_t getDepth() const;

	// void load(const std::filesystem::path& path);
	// void store(const std::filesystem::path& path) const;

	Sprite& operator=(const Sprite&) = default;

private:
	size_t            depth = 0;
	Size2i            size;
	std::vector<Tile> buffer;
};

CLEM_DEFINE_TYPE(Sprite);

} // namespace clem
