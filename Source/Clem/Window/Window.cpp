// Copyright 2021 SMS
// License(Apache-2.0)

#include "Window.h"
#include "Clem/Platform.h"
#include "Console/ConsoleWindow.h"
#include "Windows/WindowsWindow.h"
#include <cassert>

namespace clem
{

bool Window::initialized = false;

Window::Window()
{
	assert(initialized);
}

Window::~Window()
{
	assert(initialized);
}

void Window::init()
{
	assert(!initialized);
	
#if defined(USE_CONSOLE)
	ConsoleWindow::init();
#else
	WindowsWindow::init();
#endif

	initialized = true;
}

void Window::deinit()
{
	assert(initialized);

#if defined(USE_CONSOLE)
	ConsoleWindow::deinit();
#else
	WindowsWindow::deinit();
#endif

	initialized = false;
}

} // namespace clem