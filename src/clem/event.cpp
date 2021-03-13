// Copyright 2021 SMS
// License(Apache-2.0)
// 事件

#include "event.h"

Event::Event(Type type)
	: type(type)
{
}

Event::Type Event::getType() const
{
	return type;
}

