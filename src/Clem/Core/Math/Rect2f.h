// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector2f.h"

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief ��ά����, ������.
 */
class Rect2f
{
public:
	Vector2f origin;
	Size2f   size;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Rect2f() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param origin ����.
	 * @param size   ��С.
	 */
	Rect2f(const Point2f& origin, Size2f size);

	/**
	 * @brief ���캯��.
	 * 
	 * @param x      x����.
	 * @param y      y����.
	 * @param width  ��.
	 * @param height ��.
	 */
	Rect2f(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point2f tl() const;
	Point2f tr() const;
	Point2f bl() const;
	Point2f br() const;

	bool containsPoint(const Point2f& point) const;
	bool intersectsRect(const Rect2f& rect) const;
};

using Rect2 = Rect2f;

/**
 * end of Math group
 * @}
 */
