// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "Source.h"
#include "Sound.h"
#include "al_check.h"
#include <AL/al.h>
#include <cassert>

namespace audio
{

Source::Source()
{
	alGenSources(1, &handle);
}

Source::~Source()
{
	stop();
	alDeleteSources(1, &handle);
}

void Source::setSound(Sound& sound)
{
	this->sound = &sound;
}

Source::Status Source::getStatus() const
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

void Source::play()
{
	assert(sound);
	alSourcePlay(sound->getHandle());
	ALCheckError();
}

void Source::stop()
{
	assert(sound);
	alSourceStop(sound->getHandle());
	ALCheckError();
}

void Source::pause()
{
	assert(sound);
	alSourcePause(sound->getHandle());
	ALCheckError();
}

void Source::rewind()
{
	assert(sound);
	alSourceRewind(sound->getHandle());
	ALCheckError();
}

void Source::setVolume(float volume)
{
	assert(0 <= volume && volume <= 1);
	alSourcef(handle, AL_GAIN, volume);
}

float Source::getVolume() const
{
	ALfloat volume;
	alGetSourcef(handle, AL_GAIN, &volume);
	return volume;
}

void Source::setPitch(float pitch)
{
	assert(0.5f <= pitch && pitch <= 2.f);
	alSourcef(handle, AL_PITCH, pitch);
}

float Source::getPitch() const
{
	ALfloat pitch;
	alGetSourcef(handle, AL_PITCH, &pitch);
	return pitch;
}

void Source::setLoop(bool enable)
{
	alSourcei(handle, AL_LOOPING, enable);
}

void Source::setPosition(const Vector3f& pos)
{
	alSource3f(handle, AL_POSITION, pos.x, pos.y, pos.z);
}

Vector3f Source::getPosition() const
{
	ALfloat x, y, z;
	alGetSource3f(handle, AL_POSITION, &x, &y, &z);
	return {x, y, z};
}

void Source::setVelocity(const Vector3& v)
{
	alSource3f(handle, AL_VELOCITY, v.x, v.y, v.z);
}

Vector3f Source::getVelocity() const
{
	ALfloat x, y, z;
	alGetSource3f(handle, AL_VELOCITY, &x, &y, &z);
	return {x, y, z};
}

void Source::setAttenuation(float attenuation)
{
	alSourcef(handle, AL_ROLLOFF_FACTOR, attenuation);
}

float Source::getAttenuation() const
{
	ALfloat attenuation;
	alGetSourcef(handle, AL_ROLLOFF_FACTOR, &attenuation);
	return attenuation;
}

} // namespace audio
