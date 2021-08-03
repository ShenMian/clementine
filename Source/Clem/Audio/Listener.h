// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include "Core/Math/Math.h"

namespace clem
{

/**
 * @addtogroup Audio
 * @{
 */

/**
 * @brief 听者.
 */
class Listener
{
public:
	/**
	 * @brief 设置音量.
	 *
	 * @param volume 音量. 范围: [0.0, 1.0].
	 */
	static void setVolume(float volume);

	/**
	 * @brief 获取音量.
	 */
	static float getVolume();

	/**
	 * @brief 设置听者位置.
	 *
	 * @param position 听者坐标.
	 */
	static void setPosition(const Point2& position);

	/**
	 * @brief 设置听者位置.
	 *
	 * @param x 听者的 X 坐标.
	 * @param y 听者的 Y 坐标.
	 */
	static void setPosition(float x, float y);

	/**
	 * @brief 获取听者位置.
	 *
	 * @return 听者坐标.
	 */
	static Point2 getPosition();

	/**
	 * @brief 设置听者速度.
	 *
	 * @param v 听者速度.
	 */
	static void setVelocity(const Vector2& v);

	/**
	 * @brief 获取听者速度.
	 *
	 * @return 听者速度.
	 */
	static Vector2 getVelocity();
};

/**
 * end of Audio group
 * @}
 */

} // namespace clem
