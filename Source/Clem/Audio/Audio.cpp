// Copyright 2021 SMS
// License(Apache-2.0)

#include "Audio.h"
#include "Assert.hpp"
#include "Logger.h"
#include "Profiler.h"

namespace clem
{
ALCdevice*  Audio::device  = nullptr;
ALCcontext* Audio::context = nullptr;

void Audio::init()
{
    PROFILE_FUNC();
    CLEM_LOG_INFO("audio", "audio init");

    Assert::isTrue(device == nullptr, "aleardy opened a audio device");

    device = alcOpenDevice(nullptr); // 获取首选设备
    Assert::isTrue(device != nullptr, "can't open audio device");

    const ALCchar* name = nullptr;
    if(alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
        name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    if(!name || alcGetError(device) != AL_NO_ERROR)
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
    CLEM_LOG_INFO("audio", "opened audio device: '{}'", name);

    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
}

void Audio::deinit()
{
    PROFILE_FUNC();
    CLEM_LOG_INFO("audio", "audio deinit");

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    context = nullptr;
    alcCloseDevice(device);
    device = nullptr;
}
} // namespace clem