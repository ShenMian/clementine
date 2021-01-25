// Copyright 2020 SMS
// License(Apache-2.0)

#include "director.h"
#include <cassert>
#include <chrono>
#include "scene.h"
#include "platform.h"

Director* Director::getInstance()
{
	static Director getInstance;
	return &getInstance;
}

Director::Director()
		: secPerUpdate(1), paused(false)
{
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

void Director::pushScene(Scene* s)
{
	if(s == nullptr)
		assert(false);
	scenes.push_back(s);
}

void Director::popScene()
{
	if(scenes.empty())
		assert(false);
	scenes.pop_back();
}

void Director::replaceScene(Scene* s)
{
	if(scenes.empty())
		assert(false);
	scenes.front() = s;
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

#ifdef OS_UNIX

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

Size Director::getWinSize() const
{
	winsize winSize;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &winSize);
	return {winSize.ws_col, winSize.ws_row + 1};
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

#endif // OS_UNIX

#ifdef OS_WIN

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

	const auto interval = (LONGLONG)(secPerUpdate * freq.QuadPart);

	while(true)
	{
		QueryPerformanceCounter(&current);
		lag += current.QuadPart - previous.QuadPart;
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
