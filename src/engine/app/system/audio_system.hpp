// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "audio/device.h"
#include "system.hpp"

#pragma once

class AudioSystem : public System
{
public:
	AudioSystem() : System("audio") {}

	void init(Engine& engine) override { audio::Device::init(); }
	void deinit(Engine& engine) override { audio::Device::deinit(); }
};
