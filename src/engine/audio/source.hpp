// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "Sound.h"
#include "al_check.h"
#include <AL/al.h>
#include <Math/Math.hpp>
#include <cassert>

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

	Source() { alGenSources(1, &handle); }

	virtual ~Source()
	{
		stop();
		alDeleteSources(1, &handle);
	}

	/**
	 * @brief 播放.
	 */
	void play()
	{
		alSourcePlay(handle);
		ALCheckError();
	}

	/**
	 * @brief 停止播放.
	 */
	void stop()
	{
		alSourceStop(handle);
		ALCheckError();
	}

	/**
	 * @brief 暂停播放.
	 */
	void pause()
	{
		alSourcePause(handle);
		ALCheckError();
	}

	/**
	 * @brief 重绕.
	 */
	void rewind()
	{
		alSourceRewind(handle);
		ALCheckError();
	}

	/**
	 * @brief 设置声音.
	 *
	 * @param sound 声音.
	 */
	void setSound(Sound& sound)
	{
		alSourcei(handle, AL_BUFFER, sound.getHandle());
		ALCheckError();
	}

	/**
	 * @brief 获取声音播放状态.
	 */
	Status getStatus() const
	{
		ALint status;
		alGetSourcei(handle, AL_SOURCE_STATE, &status);
		switch(status)
		{
		case AL_INITIAL:
		case AL_STOPPED:
			return Status::Stopped;

		case AL_PAUSED:
			return Status::Paused;

		case AL_PLAYING:
			return Status::Playing;
		}
		return Status::Stopped;
	}

	/**
	 * @brief 设置音量.
	 *
	 * @param volume 音量. 范围: [0.0, 1.0].
	 */
	void setVolume(float volume)
	{
		assert(0 <= volume && volume <= 1);
		alSourcef(handle, AL_GAIN, volume);
	}

	/**
	 * @brief 获取音量.
	 */
	float getVolume() const
	{
		ALfloat volume;
		alGetSourcef(handle, AL_GAIN, &volume);
		return volume;
	}

	/**
	 * @brief 设置速率(倍速).
	 *
	 * @param pitch 速率. 范围: [0.5, 2.0]
	 */
	void setPitch(float pitch)
	{
		assert(0.5f <= pitch && pitch <= 2.f);
		alSourcef(handle, AL_PITCH, pitch);
	}

	/**
	 * @brief 获取速率.
	 */
	float getPitch() const
	{
		ALfloat pitch;
		alGetSourcef(handle, AL_PITCH, &pitch);
		return pitch;
	}

	/**
	 * @brief 设置是否循环播放.
	 */
	void setLoop(bool enable) { alSourcei(handle, AL_LOOPING, enable); }

	/**
	 * @brief 设置声源位置.
	 *
	 * @param pos 声源的坐标.
	 */
	void setPosition(const Vector3f& pos) { alSource3f(handle, AL_POSITION, pos.x, pos.y, pos.z); }

	/**
	 * @brief 获取声源位置.
	 */
	Vector3f getPosition() const
	{
		ALfloat x, y, z;
		alGetSource3f(handle, AL_POSITION, &x, &y, &z);
		return {x, y, z};
	}

	/**
	 * @brief 设置声源速度.
	 *
	 * @param v 声源速度.
	 */
	void setVelocity(const Vector3f& v) { alSource3f(handle, AL_VELOCITY, v.x, v.y, v.z); }

	/**
	 * @brief 获取声源速度.
	 *
	 * @return 声源速度.
	 */
	Vector3f getVelocity() const
	{
		ALfloat x, y, z;
		alGetSource3f(handle, AL_VELOCITY, &x, &y, &z);
		return {x, y, z};
	}

	/**
	 * @brief 设置衰减因子.
	 *
	 * @param attenuation 衰减因子.
	 */
	void setAttenuation(float attenuation) { alSourcef(handle, AL_ROLLOFF_FACTOR, attenuation); }

	/**
	 * @brief 获取衰减因子.
	 */
	float getAttenuation() const
	{
		ALfloat attenuation;
		alGetSourcef(handle, AL_ROLLOFF_FACTOR, &attenuation);
		return attenuation;
	}

private:
	unsigned int handle;
};

} // namespace audio