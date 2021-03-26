// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief ��ά����, ������.
 */
class Rect2
{
public:
	Vector2 origin;
	Size2   size;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Rect2() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param origin ����.
	 * @param size   ��С.
	 */
	Rect2(const Point2& origin, Size2 size);

	/**
	 * @brief ���캯��.
	 * 
	 * @param x      x����.
	 * @param y      y����.
	 * @param width  ��.
	 * @param height ��.
	 */
	Rect2(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point2 tl() const;
	Point2 tr() const;
	Point2 bl() const;
	Point2 br() const;

	bool containsPoint(const Point2& point) const;
	bool intersectsRect(const Rect2& rect) const;
};

using Rect2 = Rect2;

/**
 * end of Math group
 * @}
 */
