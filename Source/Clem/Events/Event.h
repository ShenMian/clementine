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
		mouse,
		window,

		key_press,
		key_release,
		key_repeat,

		mouse_move,
		mouse_click,
		mouse_double_click,
		mouse_wheeled,

		window_resize,
		window_close
	};

	virtual ~Event() = default;
};

#define EVENT_CLASS_TYPE(type)      \
	static Event::Type getEventType() \
	{                                 \
		return Event::Type::type;       \
	}
