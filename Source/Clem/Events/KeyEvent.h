// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

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
