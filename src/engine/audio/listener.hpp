// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include <AL/al.h>
#include <cassert>
#include <math/math.hpp>

namespace audio
{

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
	static void setVolume(float volume)
	{
		assert(0 <= volume && volume <= 1);
		alListenerf(AL_GAIN, volume);
	}

	/**
	 * @brief 获取音量.
	 */
	static float getVolume()
	{
		ALfloat volume;
		alGetListenerf(AL_GAIN, &volume);
		return volume;
	}

	/**
	 * @brief 设置听者位置.
	 *
	 * @param pos 听者的坐标.
	 */
	static void setPosition(const Vector3f& pos) { alListener3f(AL_POSITION, pos.x, pos.y, pos.z); }

	/**
	 * @brief 获取听者位置.
	 */
	static Vector3f getPosition()
	{
		ALfloat x, y, z;
		alGetListener3f(AL_POSITION, &x, &y, &z);
		return {x, y, z};
	}

	/**
	 * @brief 设置听者速度.
	 *
	 * @param v 听者速度.
	 */
	static void setVelocity(const Vector3f& v) { alListener3f(AL_VELOCITY, v.x, v.y, v.z); }

	/**
	 * @brief 获取听者速度.
	 *
	 * @return 听者速度.
	 */
	static Vector3f getVelocity()
	{
		ALfloat x, y, z;
		alGetListener3f(AL_VELOCITY, &x, &y, &z);
		return {x, y, z};
	}

	/**
	 * @brief 设置听者方向.
	 *
	 * @param pos 听者的方向.
	 */
	// static void setDirection(const Vector3f& dir);

	/**
	 * @brief 获取听者方向.
	 */
	// static Vector3f getDirection();
};

} // namespace audio
