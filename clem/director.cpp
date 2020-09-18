// Copyright 2020 SMS
// License(Apache-2.0)

#include "director.h"

Director& Director::instance()
{
	static Director instance;
	return instance;
}

void Director::setPerFrameInterval(ushort i)
{
	perFrameInterval = i;
}

void Director::mainLoop()
{
	auto scene = scenes.back();
}

