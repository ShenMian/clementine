// Copyright 2021 SMS
// License(Apache-2.0)

#include "ConsoleWindow.h"
#include "Platform.h"
#include "Rendering/Rendering.h"
#include <cassert>
#include <cstdio>

namespace fs = std::filesystem;

using std::string;

namespace clem
{

ConsoleWindow::ConsoleWindow(const std::string& title, Size2i size)
    : size(getSize())
{
    setTitle(title);
    Output::get().setSize(size);
}

void ConsoleWindow::update(Time dt)
{
    auto newSize = getSize();
    if(newSize == size)
        return;
    size = newSize;
    setSize(Size2(size.x, size.y));
    if(onResize)
        onResize(Size2(size.x, size.y));
}

void ConsoleWindow::setPosition(Size2i size)
{
    assert(false);
}

Size2i ConsoleWindow::getPosition()
{
    assert(false);
    return Size2i();
}

void ConsoleWindow::setVisible(bool visible)
{
    assert(false);
}

bool ConsoleWindow::isVisible() const
{
    return true;
}

void ConsoleWindow::setSync(bool enable)
{
    assert(false);
}

void ConsoleWindow::setIcon(const fs::path& path)
{
    assert(false);
}

void* ConsoleWindow::nativeHandle() const
{
    return nullptr;
}

// width / height = 80 / 25 => width * 25 = height * 80

#ifdef OS_UNIX

#    include <sys/ioctl.h>
#    include <termios.h>
#    include <unistd.h>

void ConsoleWindow::setTitle(const string& title)
{
    std::printf("\033]0;%s\007", title.c_str());
}

Size2i ConsoleWindow::getSize()
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

void ConsoleWindow::setSize(Size2i size)
{
    Output::get().setSize(size);
}

Size2i ConsoleWindow::getSize()
{
    return Output::get().getSize();

    /*
	const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	auto                       ret = GetConsoleScreenBufferInfo(hOut, &screenInfo);
	if(!ret)
		assert(false);
	return Size2i(screenInfo.srWindow.Right + 1, screenInfo.srWindow.Bottom + 1);
	*/
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