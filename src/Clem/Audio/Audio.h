// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <vector>
#include <filesystem>

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
