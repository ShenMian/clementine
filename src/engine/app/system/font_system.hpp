// Copyright 2022 SMS
// License(Apache-2.0)

#include "system.hpp"
#include <Graphics.h>

#pragma once

class FontSystem : public System
{
public:
	FontSystem() : System("font") {}

	void init(Engine& engine) override { Font::init(); }
	void deinit(Engine& engine) override { Font::deinit(); }
};
