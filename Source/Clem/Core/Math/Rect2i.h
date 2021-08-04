// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2.h"

namespace clem
{

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维矩形, 整型.
 */
class Rect2i
{
public:
    Vector2i origin;
    Size2i   size;

    /**
	 * @brief 默认构造函数.
	 */
    Rect2i() = default;

    /**
	 * @brief 构造函数.
	 *
	 * @param origin 矩形坐标, 左上角.
	 * @param size   矩形大小.
	 */
    Rect2i(const Point2i& origin, Size2i size);

    /**
	 * @brief 构造函数.
	 *
	 * @param x      x坐标.
	 * @param y      y坐标.
	 * @param width  宽度.
	 * @param height 高度.
	 */
    Rect2i(int x, int y, int width, int height);

    int top() const;
    int bottom() const;
    int left() const;
    int right() const;

    Point2i tl() const;
    Point2i tr() const;
    Point2i bl() const;
    Point2i br() const;

    bool containsPoint(const Point2i& point) const;
    bool intersectsRect(const Rect2i& rect) const;
};

/**
 * end of Math group
 * @}
 */

} // namespace clem