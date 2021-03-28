// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维矩形, 单精度.
 */
class Rect2
{
public:
	Vector2 origin;
	Size2   size;

	/**
	 * @brief 默认构造函数.
	 */
	Rect2() = default;

	/**
	 * @brief 构造函数.
	 *
	 * @param origin 矩形坐标, 左上角.
	 * @param size   矩形大小.
	 */
	Rect2(const Point2& origin, const Size2& size);

	/**
	 * @brief 构造函数.
	 *
	 * @param x      x坐标.
	 * @param y      y坐标.
	 * @param width  宽度.
	 * @param height 高度.
	 */
	Rect2(float x, float y, float width, float height);

	/**
	 * @brief 获取上边的 y 坐标.
	 */
	float top() const;

	/**
	 * @brief 获取下底的 y 坐标.
	 */
	float bottom() const;

	/**
	 * @brief 获取左边的 x 坐标.
	 */
	float left() const;

	/**
	 * @brief 获取右边的 x 坐标.
	 */
	float right() const;

	/**
	 * @brief 获取左上角坐标.
	 */
	Point2 tl() const;

	/**
	 * @brief 获取右上角坐标.
	 */
	Point2 tr() const;

	/**
	 * @brief 获取左下角坐标.
	 */
	Point2 bl() const;

	/**
	 * @brief 获取右下角坐标.
	 */
	Point2 br() const;

	/**
	 * @brief 检测是否与二维点发生相交.
	 *
	 * @param point 要检测的二维点的坐标.
	 * @return 相交则返回 true, 否则返回 false.
	 */
	bool intersectsPoint(const Point2& point) const;

	/**
	 * @brief 检测是否与二维矩形发生相交.
	 *
	 * @param point 要检测的二维矩形的坐标.
	 * @return 相交则返回 true, 否则返回 false.
	 */
	bool intersectsRect(const Rect2& rect) const;

	bool isValid() const;
};

/**
 * end of Math group
 * @}
 */
