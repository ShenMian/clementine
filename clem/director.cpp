// Copyright 2020 SMS
// License(Apache-2.0)

#include "scene.h"
#include "director.h"
#include "renderer.h"
#include <assert.h>

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
	thread = std::thread(&Director::loop, this);
	thread.detach();
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
	return Size();
}

void Director::loop()
{
	while(!paused)
	{
		if(scenes.empty())
			return;
		auto scene = scenes.back();

		scene->update();

		scene->render();
	}
}
