// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <Input/Mapping.h>
#include <Graphics.h>

class Editor final
{
public:
	Editor();
	~Editor();

	void loop();

	void requestExit();

	static void init();
	static void deinit();

private:
	void update(std::chrono::microseconds dt);
	void render();

	void renderUI();

	Window window;
	bool exitRequested = false;
	input::Mapping actionMap;
};
