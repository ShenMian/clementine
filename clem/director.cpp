// Copyright 2020 SMS
// License(Apache-2.0)

#include "director.h"
#include <assert.h>
#include <chrono>
#include "scene.h"
#include "terminal.h"

Director* Director::getInstance()
{
	static Director getInstance;
	return &getInstance;
}

Director::Director()
		: msPerUpdate(0), paused(false)
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

void Director::reset()
{
	msPerUpdate = 0;
	paused      = false;
	scenes.clear();
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
	scenes.back() = s;
}

Scene* Director::getCurrentScene() const
{
	if(!scenes.empty())
		return scenes.back();
	else
		return nullptr;
}

void Director::setMsPerUpdate(ushort ms)
{
	msPerUpdate = ms;
}

Size Director::getWinSize() const
{
	return Terminal::getWinSize();
}

#ifdef OS_LINUX

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

		if(lag >= msPerUpdate)
		{
			scene->update();
			lag -= msPerUpdate;
		}

		// scene->render();
	}
}

#endif // OS_LINUX

#ifdef OS_WIN

void Director::loop()
{
	LARGE_INTEGER current, previous;
	LONGLONG      lag = 0;
	QueryPerformanceCounter(&previous);

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	const auto interval = (LONGLONG)(msPerUpdate / 1000 * freq.QuadPart);

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
