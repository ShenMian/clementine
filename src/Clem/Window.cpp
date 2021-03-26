// Copyright 2021 SMS
// License(Apache-2.0)

#include "Window.h"
#include "Platform.h"
#include "Profiler.h"
#include <cassert>
#include <cstdio>

using std::string;

// width / height = 80 / 25 => width * 25 = height * 80

#ifdef OS_UNIX

#	include <sys/ioctl.h>
#	include <termios.h>
#	include <unistd.h>

void Window::setTitle(const string& title)
{
	PROFILE_FUNC();

	std::printf("\033]0;%s\007", title.c_str());
}

Size2i Window::getSize()
{
	PROFILE_FUNC();

	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return Size2(size.ws_col, size.ws_row + 1);
}

#endif

#ifdef OS_WIN

void Window::setTitle(const string& title)
{
	PROFILE_FUNC();

	SetConsoleTitleA(title.c_str());
}

Size2i Window::getSize()
{
	PROFILE_FUNC();

	const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	auto                       ret = GetConsoleScreenBufferInfo(hOut, &screenInfo);
	if(!ret)
		assert(false);
	return Size2i(screenInfo.srWindow.Right + 1, screenInfo.srWindow.Bottom + 1);
}

#endif