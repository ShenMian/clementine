// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <filesystem>
#include <vector>

#include "Listener.h"
#include "Sound.h"
#include "Source.h"

class Audio
{
public:
	typedef ALuint id_t;

	static Audio& get();

	static void init();
	static void deinit();

private:
	Audio() = default;

	static ALCdevice*  device;
	static ALCcontext* context;
};
