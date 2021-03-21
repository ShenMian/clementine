// Copyright 2021 SMS
// License(Apache-2.0)

#include "MouseEvent.h"

MouseEvent::MouseEvent(Type t, const Point& p, State s)
		: type(t), position(p), state(s)
{
}

const Point& MouseEvent::getPosition() const
{
	return position;
}

MouseEvent::State MouseEvent::getState() const
{
	return state;
}

MouseEvent::Type MouseEvent::getType() const
{
	return type;
}
