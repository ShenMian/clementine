// Copyright 2020 SMS
// License(Apache-2.0)

#include "director.h"
#include <assert.h>
#include <chrono>
#include "scene.h"
#include "renderer.h"
#include "terminal.h"

Director* Director::getInstance()
{
	static Director getInstance;
	return &getInstance;
}

Director::Director()
		: updateInterval(0), paused(false)
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

Scene* Director::getCurrentScene() const
{
	if(!scenes.empty())
		return scenes.back();
	else
		return nullptr;
}

Size Director::getWinSize() const
{
	return Terminal::getWinSize();
}

#ifdef OS_WIN

void Director::setMsPerUpdate(ushort ms)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	updateInterval = (LONGLONG)(ms / 1000 * freq.QuadPart);
}

void Director::loop()
{
	LARGE_INTEGER current, previous;
	LONGLONG      lag = 0;
	QueryPerformanceCounter(&previous);

	while(true)
	{
		if(paused)
			continue;

		auto scene = getCurrentScene();
		if(scene == nullptr)
			continue;

		QueryPerformanceCounter(&current);
		lag += current.QuadPart - previous.QuadPart;
		previous.QuadPart = current.QuadPart;

		if(lag >= updateInterval)
		{
			scene->update();
			lag -= updateInterval;
		}

		// scene->render();
	}
}

#endif // OS_WIN

#ifdef OS_LINUX

void Director::setMsPerUpdate(ushort ms)
{

}

void Director::loop()
{

}

#endif // OS_LINUX
