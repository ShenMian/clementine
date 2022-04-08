// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <Math/Math.hpp>

namespace audio
{

class Sound;

/**
 * @brief 声源.
 */
class Source
{
public:
	enum class Status
	{
		Paused,
		Playing,
		Stopped
	};

    Source();
    virtual ~Source();

    /**
	 * @brief 播放.
	 */
    void play();

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
     * @brief 设置声音.
     *
     * @param sound 声音.
     */
    void setSound(Sound& sound);

    /**
	 * @brief 设置音量.
	 *
	 * @param volume 音量. 范围: [0.0, 1.0].
	 */
    void setVolume(float volume);

    /**
	 * @brief 获取音量.
	 */
    [[nodiscard]] float getVolume() const;

    /**
	 * @brief 设置速率(倍速).
	 *
	 * @param pitch 速率. 范围: [0.5, 2.0]
	 */
    void setPitch(float pitch);

    /**
	 * @brief 获取速率.
	 */
    [[nodiscard]] float getPitch() const;

    /**
	 * @brief 设置是否循环播放.
	 */
    void setLoop(bool enable);

	/**
	 * @brief 获取声音播放状态.
	 */
    [[nodiscard]] Status getStatus() const;

    /**
	 * @brief 设置声源位置.
	 *
	 * @param pos 声源的坐标.
	 */
    void setPosition(const Vector3f& pos);

    /**
	 * @brief 获取声源位置.
	 */
    [[nodiscard]] Vector3f getPosition() const;

    /**
	 * @brief 设置声源速度.
	 *
	 * @param v 声源速度.
	 */
    void setVelocity(const Vector3f& v);

    /**
	 * @brief 获取声源速度.
	 *
	 * @return 声源速度.
	 */
    [[nodiscard]] Vector3f getVelocity() const;

    /**
	 * @brief 设置衰减因子.
	 *
	 * @param attenuation 衰减因子.
	 */
    void setAttenuation(float attenuation);

    /**
	 * @brief 获取衰减因子.
	 */
    [[nodiscard]] float getAttenuation() const;

private:
    Sound* sound = nullptr;

	unsigned int handle;
};

}
