// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "device.h"
#include "al_check.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <cstring>
#include <stdexcept>

namespace
{

ALCcontext* context;

}

namespace audio
{

Device::Device(ALCdevice* handle)
{
	if(handle == nullptr)
		throw std::runtime_error("failed to open audio device");
	handle_ = handle;

	context = alcCreateContext(handle_, nullptr);
	if(!alcMakeContextCurrent(context))
		throw std::runtime_error("failed to make current context");
}

Device::~Device()
{
	alcCloseDevice(handle_);
}

std::string_view Device::get_name() const
{
	if(alcIsExtensionPresent(handle_, "ALC_ENUMERATE_ALL_EXT"))
		return alcGetString(handle_, ALC_ALL_DEVICES_SPECIFIER);
	else
		return alcGetString(handle_, ALC_DEVICE_SPECIFIER);
}

int Device::get_sample_rate() const
{
	int frequency;
	alcGetIntegerv(handle_, ALC_FREQUENCY, 1, &frequency);
	return frequency;
}

/*
const std::vector<Device>& Device::getOutputDevices()
{
    return outputDevices;
}

const std::vector<Device>& Device::getInputDevices()
{
    return inputDevices;
}
*/

void Device::init()
{
	// 获取输出设备
	{
		if(!alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
			throw std::runtime_error("do not support enumerate output devices");

		// 设备名称列表以 '\0' 为分隔符, '\0' 作为终止符
		const char* names;
		if(alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT"))
			names = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
		else
			names = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
		if(names == nullptr)
			throw std::runtime_error("failed to get output devices name");

		auto name = names;
		while(*name != '\0')
		{
			// outputDevices.emplace_back(alcOpenDevice(name));
			name += std::strlen(name) + 1;
		}
	}

	// 获取输入设备
	{
		if(!alcIsExtensionPresent(nullptr, "ALC_EXT_capture"))
			throw std::runtime_error("do not support enumerate input devices");

		const auto names = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
		if(names == nullptr)
			throw std::runtime_error("failed to get input devices name");

		auto name = names;
		while(*name != '\0')
		{
			// inputDevices.emplace_back(alcCaptureOpenDevice(name, 44100, AL_FORMAT_STEREO16, 44100));
			name += std::strlen(name) + 1;
		}
	}
}

void Device::deinit()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	context = nullptr;
}

} // namespace audio

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
