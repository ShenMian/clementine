// Copyright 2021 SMS
// License(Apache-2.0)

#include "Window.h"
#include "Clem/Platform.h"
#include "Console/ConsoleWindow.h"
#include "Windows/WindowsWindow.h"

namespace clem
{

void Window::init()
{
#if defined(USE_CONSOLE)
	ConsoleWindow::init();
#else
	WindowsWindow::init();
#endif
}

void Window::deinit()
{
#if defined(USE_CONSOLE)
	ConsoleWindow::deinit();
#else
	WindowsWindow::deinit();
#endif
}

} // namespace clem