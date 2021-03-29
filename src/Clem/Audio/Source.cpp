// Copyright 2021 SMS
// License(Apache-2.0)

#include "Source.h"
#include <cassert>

Source::Source()
{
	alGenSources(1, &sourceId);
}

Source::~Source()
{
	stop();
	alDeleteSources(1, &sourceId);
}

void Source::play(Audio::id_t soundId)
{
	stop();
	alSourcei(sourceId, AL_BUFFER, (ALint)soundId);
	assert(alGetError() == AL_NO_ERROR);

	alSourcePlay(sourceId);
}

void Source::stop()
{
	alSourceStop(sourceId);
}

void Source::pause()
{
	alSourcePause(sourceId);
}

void Source::setVolume(float volume)
{
	assert(volume >= 0);
	alSourcef(sourceId, AL_GAIN, volume);
}

void Source::setPitch(float pitch)
{
	assert(0.5f <= pitch && pitch <= 2.0f);
	alSourcef(sourceId, AL_PITCH, pitch);
}

void Source::setLoop(bool v)
{
	alSourcei(sourceId, AL_LOOPING, v ? AL_TRUE : AL_FALSE);
}

void Source::setPosition(const Point2& p)
{
	alSource3f(sourceId, AL_POSITION, p.x, p.y, 0);
}

void Source::setVelocity(const Vector2& v)
{
	alSource3f(sourceId, AL_VELOCITY, v.x, v.y, 0);
}
