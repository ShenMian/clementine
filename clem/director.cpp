// Copyright 2020 SMS
// License(Apache-2.0)

#include "director.h"
#include <cassert>
#include <chrono>
#include "scene.h"
#include "platform.h"

#include "cursor.h"

Director Director::instance;

Director* Director::getInstance()
{
	return &instance;
}

void Director::run()
{
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

void Director::setMsPerUpdate(long ms)
{
	assert(ms > 0);

	msPerUpdate = ms;
}

#include <stdio.h>

void Director::loop()
{
	long current, previous;
	long updateLag = 0, fpsLag = 0;
	previous = getCurrentMillSecond();

	while(true)
	{
		current = getCurrentMillSecond();
		updateLag += current - previous;
		fpsLag    += current - previous;
		previous = current;

		auto scene = getCurrentScene();
		if(paused || scene == nullptr)
			continue;

		while(updateLag >= msPerUpdate)
		{
			scene->update();
			updateLag -= msPerUpdate;
		}

		scene->render();

		static int fps    = 0;
		static int frames = 0;
		frames++;
		if(fpsLag >= 1000)
		{
			fps    = frames;
			frames = fpsLag = 0;
		}
		Cursor::move(114, 29);
		printf("%d FPS", fps);
	}
}

#ifdef OS_UNIX

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

Director::Director()
		: paused(false), msPerUpdate(16)
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

long Director::getCurrentMillSecond() const
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001;
}

#endif // OS_UNIX

#ifdef OS_WIN

Director::Director()
		: paused(false), msPerUpdate(16)
{
  // 开启 VT100模式
	const auto hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD      mode;
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

long Director::getCurrentMillSecond() const
{
	LARGE_INTEGER freq;
	BOOL          ret = QueryPerformanceFrequency(&freq);
	assert(ret != 0);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time.QuadPart * 1000 / freq.QuadPart;
}

/*
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
*/

#endif // OS_WIN
