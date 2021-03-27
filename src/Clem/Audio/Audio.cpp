// Copyright 2021 SMS
// License(Apache-2.0)

#include "Audio.h"
#include <cassert>

Audio& Audio::get()
{
	static Audio instance;
	return instance;
}

Audio::Audio()
{
	device = alcOpenDevice(nullptr); // ��ȡĬ���豸
	assert(device);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);

}

Audio::~Audio()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
