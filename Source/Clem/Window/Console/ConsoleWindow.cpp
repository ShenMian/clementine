// Copyright 2021 SMS
// License(Apache-2.0)

#include "ConsoleWindow.h"
#include "Clem/Platform.h"
#include "Clem/Rendering/Output.h"
#include <cassert>
#include <cstdio>

using std::string;

namespace clem
{

ConsoleWindow::ConsoleWindow(std::string title, Size2i size)
		: size(getVisibleSize())
{
	setTitle(title);
	Output::get().setSize(size);
}

void ConsoleWindow::update()
{
	auto newSize = getVisibleSize();
	if(newSize != size)
	{
		size = newSize;
		// 分发 窗口大小改变 事件
	}
}

// width / height = 80 / 25 => width * 25 = height * 80

#ifdef OS_UNIX

#	include <sys/ioctl.h>
#	include <termios.h>
#	include <unistd.h>

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

void ConsoleWindow::init()
{
}

void ConsoleWindow::deinit()
{
}

#endif

#ifdef OS_WIN

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

void ConsoleWindow::init()
{
	DWORD mode;

	const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(!GetConsoleMode(hOut, &mode))
		assert(false);
	// mode &= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // 启用 VT100 模式 // TODO: Win10 以下會失敗
	if(!SetConsoleMode(hOut, mode))
		assert(false);

	const auto hIn = GetStdHandle(STD_INPUT_HANDLE);
	if(!GetConsoleMode(hIn, &mode))
		assert(false);
	mode &= ~ENABLE_QUICK_EDIT_MODE; // 禁用 快速编辑模式
	if(!SetConsoleMode(hIn, mode))
		assert(false);
}

void ConsoleWindow::deinit()
{
}

#endif

} // namespace clem