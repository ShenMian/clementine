// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_EVENT_KEY_EVENT_H_
#define CLEM_EVENT_KEY_EVENT_H_

#include "Event.h"

/**
 * @brief 按键事件.
 */
class KeyEvent : public Event
{
public:
	EVENT_CLASS_TYPE(key);

	short keyCode;
	bool  state;
	short repeatCount;

	KeyEvent(short keyCode, bool state, short repeatCount = 0);
};

#endif // !CLEM_EVENT_KEY_EVENT_H_
