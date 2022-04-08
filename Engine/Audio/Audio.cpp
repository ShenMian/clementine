// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Audio.h"
#include "ALCheck.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <stdexcept>

namespace
{

ALCdevice* device;
ALCcontext* context;

const ALCchar* GetDeviceName(ALCdevice* device)
{
	if(alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
		return alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
	else
		return alcGetString(device, ALC_DEVICE_SPECIFIER);
}

}

namespace audio
{

void Audio::init()
{
	if(!alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
		throw std::runtime_error("do not support enumerate devices");

	// 设备名称列表以 '\0' 为分隔符, '\0' 作为终止符
	auto names = GetDeviceName(nullptr);
	if(names == nullptr)
		throw std::runtime_error("failed to get devices name");

	auto name = names;
	while(*name != '\0')
	{
		puts(name);
		name += strlen(name) + 1;
	}

	device = alcOpenDevice(nullptr); // 获取首选设备
	if(device == nullptr)
		throw std::runtime_error("failed to open audio device");

	int frequency;
	alcGetIntegerv(device, ALC_FREQUENCY, 1, &frequency);

	puts("Audio");
	printf("Name           : %s\n", GetDeviceName(device));
	printf("Mixer frequency: %d Hz\n", frequency);

	context = alcCreateContext(device, nullptr);
	if(!alcMakeContextCurrent(context))
		throw std::runtime_error("failed to make current context");
}

void Audio::deinit()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	context = nullptr;

	alcCloseDevice(device);
	device = nullptr;
}

}

/* 录音相关代码
if(!alcIsExtensionPresent(device, "ALC_EXT_capture"))
	throw std::runtime_error("do not support capture");

auto names = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
if(names == nullptr)
	throw std::runtime_error("failed to get devices name");

auto name = names;
while(*name != '\0')
{
	puts(name);
	name += strlen(name) + 1;
}

auto device = alcCaptureOpenDevice(nullptr, 48000, AL_FORMAT_STEREO16, 1024);
if(device == nullptr)
	throw std::runtime_error("failed to open audio capture device");

alcCaptureStart(device);

char buffer[2 * (16 / 8) * 48000] = {'\0'};
while(true)
{
	int samples;
	alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, sizeof(int), &samples); // 获取捕获的音频样本数
	alcCaptureSamples(device, buffer, samples);
}

alcCaptureStop(device);

alcCaptureCloseDevice(device);
*/
