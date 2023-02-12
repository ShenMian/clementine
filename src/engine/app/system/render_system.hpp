// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "system.hpp"
#include <Graphics.h>

#pragma once

class RenderSystem : public System
{
public:
	RenderSystem() : System("render") {}

	void init(Engine& engine) override { Renderer::init(*engine.window()); }
	void deinit(Engine& engine) override { Renderer::deinit(); }
};
