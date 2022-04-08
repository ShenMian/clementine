// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <Input/Mapping.h>
#include <Graphics.h>

using std::chrono::microseconds;

class Editor final
{
public:
	Editor();
	~Editor();

	void loop();

	static void init();
	static void deinit();

private:
	void update(microseconds dt);
	void render();

	void renderUI();

	Window window;
	bool running = true;
	input::Mapping actionMap;
};
