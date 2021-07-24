// Copyright 2021 SMS
// License(Apache-2.0)

#include "WindowBase.h"
#include "Clem/GUI/GUI.h"
#include "Clem/Platform.h"
#include "ConsoleWindow.h"
#include "Window.h"
#include <cassert>

namespace clem
{

bool WindowBase::initialized = false;

WindowBase::WindowBase()
{
	assert(initialized);
}

WindowBase::~WindowBase()
{
	assert(initialized);
}

void WindowBase::add(Layer* layer)
{
	assert(std::find(layers.begin(), layers.end(), layer) == layers.end());
	layers.push_back(layer);
	layer->attach();
}

void WindowBase::remove(Layer* layer)
{
	assert(std::find(layers.begin(), layers.end(), layer) != layers.end());
	layers.erase(std::remove(layers.begin(), layers.end(), layer));
	layer->detach();
}

void WindowBase::init()
{
	assert(!initialized);

#if defined(USE_CONSOLE)
	ConsoleWindow::init();
#else
	GlfwWindow::init();
#endif

	initialized = true;
}

void WindowBase::deinit()
{
	assert(initialized);

#if defined(USE_CONSOLE)
	ConsoleWindow::deinit();
#else
	GlfwWindow::deinit();
#endif

	initialized = false;
}

} // namespace clem