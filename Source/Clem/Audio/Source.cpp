// Copyright 2021 SMS
// License(Apache-2.0)

#include "Source.h"
#include "Core/Assert.hpp"
#include "Sound.h"

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

void Source::play(const Sound& s)
{
    stop();
    alSourcei(id, AL_BUFFER, s.getBufferId());
    Assert::isTrue(alGetError() == AL_NO_ERROR);
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
    Assert::isTrue(0 <= v && v <= 1);
    alSourcef(id, AL_GAIN, v);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

float Source::getVolume()
{
    ALfloat v;
    alGetSourcef(id, AL_GAIN, &v);
    return v;
}

void Source::setPitch(float p)
{
    Assert::isTrue(0.5f <= p && p <= 2.f);
    alSourcef(id, AL_PITCH, p);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

void Source::setLoop(bool v)
{
    alSourcei(id, AL_LOOPING, v ? AL_TRUE : AL_FALSE);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

void Source::setPosition(const Point3& p)
{
    alSource3f(id, AL_POSITION, p.x, p.y, p.z);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

void Source::setPosition(float x, float y, float z)
{
    setPosition({x, y, z});
}

Point3 Source::getPosition()
{
    ALfloat x, y, z;
    alGetSource3f(id, AL_POSITION, &x, &y, &z);
    return {x, y, z};
}

void Source::setVelocity(const Vector3& v)
{
    alSource3f(id, AL_VELOCITY, v.x, v.y, v.z);
    Assert::isTrue(alGetError() == AL_NO_ERROR);
}

void Source::setVelocity(float x, float y, float z)
{
    setVelocity({x, y, z});
}

Vector3 Source::getVelocity()
{
    ALfloat x, y, z;
    alGetSource3f(id, AL_VELOCITY, &x, &y, &z);
    return {x, y, z};
}

Source::Status Source::getStatus() const
{
    ALint status;
    alGetSourcei(id, AL_SOURCE_STATE, &status);

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

    Assert::isTrue(false, "unknown status");
    return Status::Stopped;
}

Source::operator id_t() const
{
    return id;
}

} // namespace clem