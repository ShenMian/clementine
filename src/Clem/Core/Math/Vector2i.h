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
 * @brief ��ά����, ����.
 */
struct Vector2i
{
	int x = 0;
	int y = 0;

	/**
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Vector2i() = default;

	/**
	 * @brief ���캯��.
	 * 
	 * @param x x����.
	 * @param y y����.
	 */
	Vector2i(int x, int y);
};

Vector2i::Vector2i(int x, int y)
		: x(x), y(y)
{
}
