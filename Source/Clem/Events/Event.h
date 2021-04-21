// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

/**
 * @brief 事件.
 */
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

#define EVENT_CLASS_TYPE(type)      \
	static Event::Type getEventType() \
	{                                 \
		return Event::Type::type;       \
	}
