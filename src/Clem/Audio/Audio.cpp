// Copyright 2021 SMS
// License(Apache-2.0)

#include "Audio.h"
#include "Clem.h"
#include <fstream>
#include <stdint.h>

using namespace clem;
using namespace std::filesystem;

ALCdevice*  Audio::device;
ALCcontext* Audio::context;

Audio& Audio::get()
{
	static Audio instance;
	return instance;
}

void Audio::init()
{
	PROFILE_FUNC();

	device = alcOpenDevice(nullptr); // 获取默认设备
	Assert::isNotNull(device, "can't open audio device", CALL_INFO);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);
}

void Audio::deinit()
{
	PROFILE_FUNC();

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}