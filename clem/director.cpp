// Copyright 2020 SMS
// License(Apache-2.0)

#include "director.h"
#include <cassert>
#include <chrono>
#include "scene.h"
#include "platform.h"

Director Director::instance;

Director* Director::getInstance()
{
	return &instance;
}

void Director::run()
{
	if(scenes.empty())
		assert(false);

	loop();
}

void Director::pause()
{
	if(paused)
		assert(false);

	paused = true;	
}

void Director::resume()
{
	if(!paused)
		assert(false);

	paused = false;
}

void Director::pushScene(Scene& s)
{
	scenes.push_back(&s);
}

void Director::popScene()
{
	if(scenes.empty())
		assert(false);

	scenes.pop_back();
}

void Director::replaceScene(Scene& s)
{
	if(scenes.empty())
		assert(false);

	scenes.front() = &s;
}

Scene* Director::getCurrentScene() const
{
	if(!scenes.empty())
		return scenes.back();
	else
		return nullptr;
}

void Director::setSecPerUpdate(float sec)
{
	assert(sec > 0);

	secPerUpdate = sec;
}

#ifndef OS_WIN

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

Director::Director()
		: paused(false), secPerUpdate(1)
{
  // 开启 raw 模式
  termios mode;
  if(tcgetattr(STDOUT_FILENO, &mode) == -1)
		assert(false);
	mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	mode.c_cflag |= (CS8);
	mode.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	mode.c_cc[VMIN]  = 0;
	mode.c_cc[VTIME] = 0;
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &mode) == -1)
    assert(false);
}

Size Director::getWinSize() const
{
	winsize winSize;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &winSize);
	return Size(winSize.ws_col, winSize.ws_row + 1);
}

#include <sys/time.h>

long getCurrentMillSecond()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001; // milliseconds
}

void Director::loop()
{
	long current, previous, lag = 0;
	previous = getCurrentMillSecond();

	while(true)
	{
		if(paused)
			continue;

		auto scene = getCurrentScene();
		if(scene == nullptr)
			continue;

		current = getCurrentMillSecond();

		if(lag >= secPerUpdate / 1000)
		{
			scene->update();
			lag -= secPerUpdate;
		}

		scene->render();
	}
}

#endif // !OS_WIN

#ifdef OS_WIN

Director::Director()
		: secPerUpdate(1), paused(false)
{
  // 开启 VT100 模式
	auto  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	if(!GetConsoleMode(hStdOut, &mode))
		assert(false);
	if(!SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		assert(false);
}

Size Director::getWinSize() const
{
	static const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	auto ret = GetConsoleScreenBufferInfo(hOut, &screenInfo);
	if(!ret)
		assert(false);

	return Size(screenInfo.srWindow.Right + 1, screenInfo.srWindow.Bottom + 1);
}

void Director::loop()
{
	LARGE_INTEGER current, previous, freq;
	long          lag = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&previous);

	const long interval = secPerUpdate * freq.QuadPart;

	while(true)
	{
		QueryPerformanceCounter(&current);
		lag += (long)(current.QuadPart - previous.QuadPart);
		previous.QuadPart = current.QuadPart;

		auto scene = getCurrentScene();
		if(paused || scene == nullptr)
			continue;

		while(lag >= interval)
		{
			scene->update();
			lag -= interval;
		}

		scene->render();
	}
}

#endif // OS_WIN
