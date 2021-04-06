﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include "Clem/Core/Math/Math.h"

namespace clem
{
class Sound;

/**
 * @brief 声源.
 */
class Source
{
public:
	typedef ALuint id_t;

	Source();
	~Source();

	/**
	 * @brief 播放声音.
	 *
	 * @param s 要播放的声音.
	 */
	void play(Sound& s);

	/**
	 * @brief 停止播放.
	 */
	void stop();

	/**
	 * @brief 暂停播放.
	 */
	void pause();

	/**
	 * @brief 设置音量.
	 *
	 * @param volume 音量. 范围: 0.0 - 1.0.
	 */
	void setVolume(float volume);

	/**
	 * @brief 设置速率(倍速).
	 *
	 * @param pitch 速率. 范围: 0.5 - 2.0
	 */
	void setPitch(float pitch);

	/**
	 * @brief 设置是否循环播放.
	 */
	void setLoop(bool);

	/**
	 * @brief 设置声源位置.
	 *
	 * @param p 坐标.
	 */
	void setPosition(const Point2& p);

	/**
	 * @brief 设置声源速度.
	 *
	 * @param v 速度.
	 */
	void setVelocity(const Vector2& v);

private:
	id_t id;
};
} // namespace clem
