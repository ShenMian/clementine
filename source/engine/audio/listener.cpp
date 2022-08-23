// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "Listener.h"
#include "AL/al.h"
#include <cassert>

namespace audio
{

void Listener::setVolume(float volume)
{
	assert(0 <= volume && volume <= 1);
	alListenerf(AL_GAIN, volume);
}

float Listener::getVolume()
{
	ALfloat volume;
	alGetListenerf(AL_GAIN, &volume);
	return volume;
}

void Listener::setPosition(const Vector3f& pos)
{
	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
}

Vector3f Listener::getPosition()
{
	ALfloat x, y, z;
	alGetListener3f(AL_POSITION, &x, &y, &z);
	return {x, y, z};
}

void Listener::setVelocity(const Vector3f& v)
{
	alListener3f(AL_VELOCITY, v.x, v.y, v.z);
}

Vector3f Listener::getVelocity()
{
	ALfloat x, y, z;
	alGetListener3f(AL_VELOCITY, &x, &y, &z);
	return {x, y, z};
}

} // namespace audio
