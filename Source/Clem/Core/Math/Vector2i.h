﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

namespace clem
{

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 二维向量, 整型.
 */
class Vector2i
{
public:
    int x = 0;
    int y = 0;

    /**
	 * @brief 构造函数.
	 */
    Vector2i() = default;

    /**
	 * @brief 构造函数.
	 *
	 * @param x x坐标.
	 * @param y y坐标.
	 */
    Vector2i(int x, int y);

    /**
	 * @brief 获取面积.
	 */
    int area() const;

    bool      operator==(const Vector2i& v) const;
    bool      operator!=(const Vector2i& v) const;
    Vector2i  operator*(int n) const;
    Vector2i  operator/(int n) const;
    Vector2i  operator+(const Vector2i& v) const;
    Vector2i  operator-(const Vector2i& v) const;
    Vector2i  operator-() const;
    Vector2i& operator+=(const Vector2i& v);
    Vector2i& operator-=(const Vector2i& v);
    Vector2i& operator*=(int n);
    Vector2i& operator/=(int n);
};

using Point2i = Vector2i;
using Size2i  = Vector2i;

/**
 * end of Math group
 * @}
 */

} // namespace clem