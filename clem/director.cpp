// Copyright 2020 SMS
// License(Apache-2.0)

#include "scene.h"
#include "director.h"
#include "nocolor_renderer.h"
#include <assert.h>

Director& Director::instance()
{
	static Director instance;
	return instance;
}

void Director::run()
{
	thread = std::thread(&Director::loop, this);
	thread.detach();
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

Director::Director()
		: msPerUpdate(0), renderer(new NocolorRenderer())
{
}

void Director::loop()
{
	while(true)
	{
		if(scenes.empty())
			return;
		auto scene = scenes.back();

		scene->update();

		scene->render(renderer);
	}
}
