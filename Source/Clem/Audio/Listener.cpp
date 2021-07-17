// Copyright 2021 SMS
// License(Apache-2.0)

#include "Listener.h"
#include <cassert>

namespace clem
{
void Listener::setVolume(float v)
{
	assert(0 <= v && v <= 1);
	alListenerf(AL_GAIN, v);
	assert(alGetError() == AL_NO_ERROR);
}

float Listener::getVolume()
{
	ALfloat v;
	alGetListenerf(AL_GAIN, &v);
	return v;
}

void Listener::setPosition(float x, float y)
{
	setPosition(Point2(x, y));
}

void Listener::setPosition(const Point2& p)
{
	alListener3f(AL_POSITION, p.x, p.y, 0);
	assert(alGetError() == AL_NO_ERROR);
}

Point2 Listener::getPosition()
{
	ALfloat x, y, z;
	alGetListener3f(AL_POSITION, &x, &y, &z);
	return Point2(x, y);
}

void Listener::setVelocity(const Vector2& v)
{
	alListener3f(AL_VELOCITY, v.x, v.y, 0);
	assert(alGetError() == AL_NO_ERROR);
}

Vector2 Listener::getVelocity()
{
	ALfloat x, y, z;
	alGetListener3f(AL_VELOCITY, &x, &y, &z);
	return Vector2(x, y);
}
} // namespace clem