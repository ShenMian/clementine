// Copyright 2020 SMS
// License(Apache-2.0)
// 输入

#include "input.h"
#include <time.h>
#include <clem/observable.h>

using std::vector;

void Input::update()
{
				events.clear();
				
				scan();
				
				static vector<ushort> lastEvents;
				static clock_t        lastTime;

				auto now = clock();
				if(events == lastEvents && now - lastTime < interval)
								events.clear();
				else
				{
								lastEvents = events;
								lastTime   = now;
				}

				notifyObserver();
}

void Input::notifyObserver() const
{
	for(auto o : observers)
		o->onNotify(*this);
}

const vector<InputEvent> Input::getEvents() const
{
				return events;
}

void Input::bind(ushort code, const InputEvent& event)
{
	auto ret = index.find(code);
	if(ret == index.end())
		index.insert({code, event});
	else
		ret->second = event;
}

void Input::setInterval(ushort ms)
{
	interval = ms;
}

ushort Input::getInterval() const
{
	return interval;
}
