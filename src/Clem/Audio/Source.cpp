// Copyright 2021 SMS
// License(Apache-2.0)

#include "Source.h"
#include "Sound.h"
#include <cassert>

Source::Source()
{
	alGenSources(1, &id);
}

Source::~Source()
{
	stop();
	alDeleteSources(1, &id);
}

void Source::play(Sound& s)
{
	stop();
	alSourcei(id, AL_BUFFER, s);
	assert(alGetError() == AL_NO_ERROR);
	alSourcePlay(id);
}

void Source::stop()
{
	alSourceStop(id);
}

void Source::pause()
{
	alSourcePause(id);
}

void Source::setVolume(float volume)
{
	assert(volume >= 0);
	alSourcef(id, AL_GAIN, volume);
}

void Source::setPitch(float pitch)
{
	assert(0.5f <= pitch && pitch <= 2.0f);
	alSourcef(id, AL_PITCH, pitch);
}

void Source::setLoop(bool v)
{
	alSourcei(id, AL_LOOPING, v ? AL_TRUE : AL_FALSE);
}

void Source::setPosition(const Point2& p)
{
	alSource3f(id, AL_POSITION, p.x, p.y, 0);
}

void Source::setVelocity(const Vector2& v)
{
	alSource3f(id, AL_VELOCITY, v.x, v.y, 0);
}
