// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Audio.h"
#include "Clem/Core/Math/Math.h"
#include "AL/alext.h"

class Sound;

class Source
{
public:
	typedef ALuint id_t;

	Source();
	~Source();

	void play(Sound&);
	void stop();
	void pause();

	void setVolume(float volume);
	void setPitch(float pitch);
	void setLoop(bool);

	void setPosition(const Point2& p);
	void setVelocity(const Vector2& v);

private:
	id_t id;
};
