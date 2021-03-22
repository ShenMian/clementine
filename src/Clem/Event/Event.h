// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_EVENT_EVENT_H_
#define CLEM_EVENT_EVENT_H_

class Event
{
public:
	enum class Type
	{
		key,
		mouse
	};

	virtual ~Event() = default;
};

#define EVENT_CLASS_TYPE(type) static Event::Type getEventType() { return Event::Type::type; }

#endif // !CLEM_EVENT_EVENT_H_
