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
	 * @param pos 听者坐标.
	 */
    static void setPosition(const Point3& pos);

    /**
	 * @brief 设置听者位置.
	 *
	 * @param x 听者的 X 坐标.
	 * @param y 听者的 Y 坐标.
	 * @param z 听者的 Z 坐标.
	 */
    static void setPosition(float x, float y, float z = 0.f);

    /**
	 * @brief 获取听者位置.
	 *
	 * @return 听者坐标.
	 */
    static Point3 getPosition();

    /**
	 * @brief 设置听者速度.
	 *
	 * @param v 听者速度.
	 */
    static void setVelocity(const Vector3& v);

    /**
	 * @brief 设置听者速度.
	 *
	 * @param x 听者 X 方向上的速度.
	 * @param y 听者 Y 方向上的速度.
	 * @param y 听者 Y 方向上的速度.
	 */
    static void setVelocity(float x, float y, float z = 0.f);

    /**
	 * @brief 获取听者速度.
	 *
	 * @return 听者速度.
	 */
    static Vector3 getVelocity();
};

/**
 * end of Audio group
 * @}
 */

} // namespace clem
