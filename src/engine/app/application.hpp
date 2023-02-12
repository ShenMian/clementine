// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "core/time.hpp"
#include <Graphics.h>
#include <string>

#pragma once

class Application
{
public:
	struct Config
	{
		struct About
		{
			std::string name;
			std::string description;
		} about;

		struct Window
		{
			std::string title;
		} window;
	};

	Application(const Config& config) : config_(config) {}

	virtual void update(core::Time dt) = 0;
	virtual void init()                = 0;
	virtual void deinit()              = 0;

private:
	Config config_;
};
