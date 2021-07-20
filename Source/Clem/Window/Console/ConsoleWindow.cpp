// Copyright 2021 SMS
// License(Apache-2.0)

#include "ConsoleWindow.h"
#include "Clem/Platform.h"
#include <cassert>
#include <cstdio>

using std::string;

namespace clem
{

// width / height = 80 / 25 => width * 25 = height * 80

#ifdef OS_UNIX

#	include <sys/ioctl.h>
#	include <termios.h>
#	include <unistd.h>

void ConsoleWindow::update()
{
}

void ConsoleWindow::setTitle(const string& title)
{
	std::printf("\033]0;%s\007", title.c_str());
}

Size2i ConsoleWindow::getVisibleSize()
{
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return Size2(size.ws_col, size.ws_row + 1);
}

#endif

#ifdef OS_WIN

void ConsoleWindow::update()
{
}

void ConsoleWindow::setTitle(const string& title)
{
	SetConsoleTitleA(title.c_str());
}

Size2i ConsoleWindow::getVisibleSize()
{
	const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	auto                       ret = GetConsoleScreenBufferInfo(hOut, &screenInfo);
	if(!ret)
		assert(false);
	return Size2i(screenInfo.srWindow.Right + 1, screenInfo.srWindow.Bottom + 1);
}

#endif

} // namespace clem