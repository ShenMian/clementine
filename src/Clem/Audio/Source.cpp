// Copyright 2021 SMS
// License(Apache-2.0)

#include "Source.h"
#include "Sound.h"
#include <cassert>

namespace clem
{
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

void Source::rewind()
{
	alSourceRewind(id);
}

void Source::setVolume(float v)
{
	assert(0 <= v && v <= 1);
	alSourcef(id, AL_GAIN, v);
	assert(alGetError() == AL_NO_ERROR);
}

float Source::getVolume()
{
	ALfloat v;
	alGetSourcef(id, AL_GAIN, &v);
	return v;
}

void Source::setPitch(float p)
{
	assert(0.5f <= p && p <= 2.0f);
	alSourcef(id, AL_PITCH, p);
	assert(alGetError() == AL_NO_ERROR);
}

void Source::setLoop(bool v)
{
	alSourcei(id, AL_LOOPING, v ? AL_TRUE : AL_FALSE);
	assert(alGetError() == AL_NO_ERROR);
}

void Source::setPosition(const Point2& p)
{
	alSource3f(id, AL_POSITION, p.x, p.y, 0);
	assert(alGetError() == AL_NO_ERROR);
}

Point2 Source::getPosition()
{
	ALfloat x, y, z;
	alGetSource3f(id, AL_POSITION, &x, &y, &z);
	return Point2(x, y);
}

void Source::setVelocity(const Vector2& v)
{
	alSource3f(id, AL_VELOCITY, v.x, v.y, 0);
	assert(alGetError() == AL_NO_ERROR);
}

Vector2 Source::getVelocity()
{
	ALfloat x, y, z;
	alGetSource3f(id, AL_VELOCITY, &x, &y, &z);
	return Point2(x, y);
}
} // namespace clem