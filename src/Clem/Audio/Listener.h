// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include "Clem/Core/Math/Math.h"

/**
 * @brief 听者.
 */
class Listener
{
public:
	/**
	 * @brief 设置声源位置.
	 * 
	 * @param p 坐标.
	 */
	static void setPosition(const Point2& p);

	/**
	 * @brief 设置声源速度.
	 * 
	 * @param v 速度.
	 */
	static void setVelocity(const Vector2& v);
};
