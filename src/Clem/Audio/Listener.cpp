// Copyright 2021 SMS
// License(Apache-2.0)

#include "Listener.h"

void Listener::setPosition(const Point2& p)
{
	alListener3f(AL_POSITION, p.x, p.y, 0);
}

void Listener::setVelocity(const Vector2& v)
{
	alListener3f(AL_VELOCITY, v.x, v.y, 0);
}
