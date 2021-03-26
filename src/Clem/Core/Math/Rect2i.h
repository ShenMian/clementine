// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief ��ά����, ����.
 */
class Rect2i
{
public:
	Vector2i origin;
	Size2i   size;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Rect2i() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param origin ����.
	 * @param size   ��С.
	 */
	Rect2i(const Point2i& origin, Size2i size);

	/**
	 * @brief ���캯��.
	 * 
	 * @param x      x����.
	 * @param y      y����.
	 * @param width  ��.
	 * @param height ��.
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
