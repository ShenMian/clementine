// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_EVENT_EVENT_DISPATCHER_H_
#define CLEM_EVENT_EVENT_DISPATCHER_H_

#include "Event.h"
#include <map>
#include <functional>

class EventDispatcher
{
public:
	typedef std::function<void(Event*)> listener_t;
	
	static EventDispatcher& getInstance();

	template<class T>
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

#endif // !CLEM_EVENT_EVENT_DISPATCHER_H_
