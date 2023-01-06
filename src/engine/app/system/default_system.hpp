// Copyright 2022 SMS
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
		if(!engine.hasSystem<WindowSystem>())
			engine.addSystem<WindowSystem>();
		if(!engine.hasSystem<RenderSystem>())
			engine.addSystem<RenderSystem>();
		if(!engine.hasSystem<AudioSystem>())
			engine.addSystem<AudioSystem>();
		if(!engine.hasSystem<FontSystem>())
			engine.addSystem<FontSystem>();
	}
	void deinit(Engine& engine) override {}
};
