// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include "Core/Math/Math.h"

namespace clem
{
class Sound;

/**
 * @addtogroup Audio
 * @{
 */

/**
 * @brief 声源.
 */
class Source
{
public:
    typedef ALuint id_t;

    enum class Status
    {
        Paused,
        Playing,
        Stopped
    };

    Source();
    ~Source();

    /**
	 * @brief 播放声音.
	 *
	 * @param s 要播放的声音.
	 */
    void play(const Sound& s);

    /**
	 * @brief 停止播放.
	 */
    void stop();

    /**
	 * @brief 暂停播放.
	 */
    void pause();

    /**
	 * @brief 重绕.
	 */
    void rewind();

    /**
	 * @brief 设置音量.
	 *
	 * @param volume 音量. 范围: [0.0, 1.0].
	 */
    void setVolume(float volume);

    /**
	 * @brief 获取音量.
	 */
    float getVolume();

    /**
	 * @brief 设置速率(倍速).
	 *
	 * @param pitch 速率. 范围: [0.5, 2.0]
	 */
    void setPitch(float pitch);

    /**
	 * @brief 设置是否循环播放.
	 */
    void setLoop(bool);

    /**
	 * @brief 设置声源位置.
	 *
	 * @param pos 声源的坐标.
	 */
    void setPosition(const Point3& pos);

    /**
	 * @brief 设置声源位置.
	 *
	 * @param x 声源的 X 坐标.
	 * @param y 声源的 Y 坐标.
	 * @param z 声源的 Z 坐标.
	 */
    void setPosition(float x, float y, float z = 0.f);

    /**
	 * @brief 获取声源位置.
	 *
	 * @return 声源坐标.
	 */
    Point3 getPosition();

    /**
	 * @brief 设置声源速度.
	 *
	 * @param v 速度.
	 */
    void setVelocity(const Vector3& v);

    /**
	 * @brief 设置声源速度.
	 *
	 * @param x 声源 X 方向上的速度.
	 * @param y 声源 Y 方向上的速度.
	 * @param y 声源 Y 方向上的速度.
	 */
    void setVelocity(float x, float y, float z = 0.f);

    /**
	 * @brief 获取声源速度.
	 *
	 * @return 声源速度.
	 */
    Vector3 getVelocity();

    Status getStatus() const;

    operator id_t() const;

private:
    id_t id;
};

/**
 * end of Audio group
 * @}
 */
} // namespace clem
