// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Event.h"
#include <functional>
#include <map>

/**
 * @brief 事件分发器.
 * 
 * @note 观察者模式.
 */
class EventDispatcher
{
public:
	typedef std::function<void(Event*)> listener_t;

	static EventDispatcher& get();

	template <class T>
	void dispatch(T& event);

	void addListener(Event::Type type, const listener_t& listener);

private:
	EventDispatcher() = default;

	std::multimap<Event::Type, listener_t> listeners;
};

template <class T>
void EventDispatcher::dispatch(T& event)
{
	for(auto& listener : listeners)
	{
		if(T::getEventType() == listener.first)
			listener.second(&event);
	}
}
