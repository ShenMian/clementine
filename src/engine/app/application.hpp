// Copyright 2022 SMS
// License(Apache-2.0)

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

	Application(const Config& config) : config_(config)
	{
		/*
		Renderer::init(window_);
		UI::init(window_);
		Input::setWindow(window_);
		*/
	}

	virtual void update(float dt) = 0;
	virtual void init()           = 0;
	virtual void deinit()         = 0;

private:
	Config config_;
};
