// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Editor.h"
#include <Input/KeyTrigger.h>
#include <Input/ChordTrigger.h>
#include <Audio/Sound.h>
#include <Audio/Source.h>
#include <Audio/Listener.h>
#include <Audio/Audio.h>
#include <thread>

using namespace audio;
using namespace input;

Editor::Editor()
	: window("Editor", {1920 / 2, 1080 / 2})
{
	Renderer::init(window);
	UI::init(window);
	Input::setWindow(window);

	actionMap.add(std::make_shared<KeyTrigger>(Key::Escape), [this]() { this->running = false; });

	window.setVisible(true);
}

Editor::~Editor()
{
	UI::deinit();
	Renderer::deinit();
}

void Editor::loop()
{
	auto prev = std::chrono::high_resolution_clock::now();
	while(running)
	{
		const auto curr = std::chrono::high_resolution_clock::now();
		const auto dt = std::chrono::duration_cast<microseconds>(curr - prev);
		prev = curr;

		update(dt);
		render();
	}
}

void Editor::update(microseconds dt)
{
	actionMap.update();
	window.update();
}

void Editor::render()
{
	renderUI();
}

void Editor::renderUI()
{
	UI::beginFrame();

	UI::endFrame();
}

void Editor::init()
{
	Renderer::setAPI(Renderer::API::OpenGL);

	Audio::init();
	Window::init();
}

void Editor::deinit()
{
	Window::deinit();
	Audio::deinit();
}
