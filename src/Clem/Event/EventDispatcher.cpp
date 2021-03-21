// Copyright 2021 SMS
// License(Apache-2.0)

#include "EventDispatcher.h"

EventDispatcher& EventDispatcher::getInstance()
{
	static EventDispatcher instance;
	return instance;
}

void EventDispatcher::addListener(Event::Type t, const listener_t& l)
{
	listeners.insert({t, l});
}
