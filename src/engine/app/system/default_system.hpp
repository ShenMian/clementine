// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "app/engine.hpp"
#include "audio/device.h"
#include "audio_system.hpp"
#include "font_system.hpp"
#include "render_system.hpp"
#include "system.hpp"
#include "window_system.hpp"

#pragma once

class DefaultSystem : public System
{
public:
	DefaultSystem() : System("default") {}

	void init(Engine& engine) override
	{
		if(!engine.has_system<WindowSystem>())
			engine.add_system<WindowSystem>();
		if(!engine.has_system<RenderSystem>())
			engine.add_system<RenderSystem>();
		if(!engine.has_system<AudioSystem>())
			engine.add_system<AudioSystem>();
		if(!engine.has_system<FontSystem>())
			engine.add_system<FontSystem>();
	}
	void deinit(Engine& engine) override {}
};
