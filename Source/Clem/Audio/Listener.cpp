// Copyright 2021 SMS
// License(Apache-2.0)

#include "Listener.h"
#include "Core/Assert.hpp"

namespace clem
{

void Listener::setVolume(float v)
{
    Assert::isTrue(0 <= v && v <= 1);
    alListenerf(AL_GAIN, v);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

float Listener::getVolume()
{
    ALfloat v;
    alGetListenerf(AL_GAIN, &v);
    return v;
}

void Listener::setPosition(const Point3& pos)
{
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

void Listener::setPosition(float x, float y, float z)
{
    setPosition({x, y, z});
}

Point3 Listener::getPosition()
{
    ALfloat x, y, z;
    alGetListener3f(AL_POSITION, &x, &y, &z);
    return Point3(x, y, z);
}

void Listener::setVelocity(const Vector3& v)
{
    alListener3f(AL_VELOCITY, v.x, v.y, 0);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

void Listener::setVelocity(float x, float y, float z)
{
    setVelocity({x, y, z});
}

Vector3 Listener::getVelocity()
{
    ALfloat x, y, z;
    alGetListener3f(AL_VELOCITY, &x, &y, &z);
    return Vector3(x, y, z);
}

} // namespace clem