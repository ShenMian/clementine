// Copyright 2020 SMS
// License(Apache-2.0)

#include "scene.h"
#include "director.h"
#include "renderer.h"
#include "terminal.h"
#include <assert.h>
#include <chrono>

Director* Director::instance()
{
	static Director instance;
	return &instance;
}

Director::Director()
		: msPerUpdate(0), paused(false)
{
}

void Director::run()
{
	assert(!scenes.empty());
	loop();

	// thread = std::thread(&Director::loop, this);
	// thread.detach();
}


void Director::pause()
{
	assert(!paused);
	paused = true;	
}

void Director::resume()
{
	assert(paused);
	paused = false;
}

void Director::setMsPerUpdate(ushort i)
{
	msPerUpdate = i;
}

void Director::pushScene(Scene* s)
{
	assert(s != nullptr);
	scenes.push_back(s);
}

void Director::popScene()
{
	assert(!scenes.empty());
	scenes.pop_back();
}

Scene* Director::getRunningScene() const
{
	return scenes.back();
}

Size Director::getWinSize() const
{
	return Terminal::getWinSize();
}

void Director::loop()
{
	long long lag = 0;

	while(true)
	{
		auto previous = std::chrono::steady_clock::now();
		auto current  = std::chrono::steady_clock::now();
		lag += std::chrono::duration_cast<std::chrono::microseconds>(current - previous).count();

		if(paused)
			continue;

		if(scenes.empty())
			return;
		auto scene = scenes.back();

		if(lag > msPerUpdate)
		{
			scene->update();
			lag -= msPerUpdate;
		}

		scene->render();
	}
}
