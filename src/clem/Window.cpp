// Copyright 2021 SMS
// License(Apache-2.0)

#include "Window.h"
#include "Platform.h"
#include <cassert>

using std::string;

void Window::setTitle(string& title)
{
}

#ifdef OS_UNIX

Size Window::getSize()
{
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	// return(size.ws_col, size.ws_row + 1);

	// width / height = 80 / 25 => width * 25 = height * 80
	const short width  = 80;
	const short height = width * 25 / 80;
	return Size(width, height);
}

#endif

#ifdef OS_WIN

Size Window::getSize()
{
	const auto                 hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	auto                       ret = GetConsoleScreenBufferInfo(hOut, &screenInfo);
	if(!ret)
		assert(false);
	// return Size(screenInfo.srWindow.Right + 1, screenInfo.srWindow.Bottom + 1);

	// width / height = 80 / 25 => width * 25 = height * 80
	const short width  = 80;
	const short height = width * 25 / 80;
	return Size(width, height);
}

#endif
