// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alc.h"

class Audio
{
public:
	static Audio& get();

private:
	Audio();
	~Audio();

	ALCdevice*  device;
	ALCcontext* context;
};
