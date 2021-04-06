// Copyright 2021 SMS
// License(Apache-2.0)

#include "Audio.h"
#include "Clem.h"
#include <fstream>
#include <stdint.h>

using namespace clem;
using namespace std::filesystem;

ALCdevice*  Audio::device  = nullptr;
ALCcontext* Audio::context = nullptr;

Audio& Audio::get()
{
	static Audio instance;
	return instance;
}

void Audio::init()
{
	PROFILE_FUNC();

	Assert::isNull(device, "aleardy opened a audio device", CALL_INFO);
	device = alcOpenDevice(nullptr); // 获取首选设备
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
	context = nullptr;
	device  = nullptr;
}