// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "system.hpp"
#include <Graphics.h>

#pragma once

class WindowSystem : public System
{
public:
	WindowSystem() : System("window") {}

	void init(Engine& engine) override
	{
		Window::init();
		engine.window(std::make_shared<Window>("", Vector2i{960, 540}));
	}

	void deinit(Engine& engine) override { Window::deinit(); }
};
