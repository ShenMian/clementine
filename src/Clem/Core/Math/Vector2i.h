// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>

struct Vector2f;

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维向量, 整型.
 */
struct Vector2i
{
	int x = 0;
	int y = 0;

	/**
	 * @brief 默认构造函数.
	 */
	Vector2i() = default;

	/**
	 * @brief 构造函数.
	 * 
	 * @param x x坐标.
	 * @param y y坐标.
	 */
	Vector2i(int x, int y);
};

Vector2i::Vector2i(int x, int y)
		: x(x), y(y)
{
}
