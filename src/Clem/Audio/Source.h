// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Audio.h"
#include "Clem/Core/Math/Math.h"
#include "AL/alext.h"

class Source
{
public:
	void play(Audio::id_t id);
	void stop();

	void setVolume(float);
	void setPitch(float);
	void setLoop(bool);

	void setPosition(const Point2& p);
	void setVelocity(const Vector2& v);
};
