// Copyright 2021 SMS
// License(Apache-2.0)

#include "MouseEvent.h"

MouseEvent::MouseEvent(Type t, const Point2& p, Key s)
		: type(t), position(p), key(s)
{
}

const Point2& MouseEvent::getPosition() const
{
	return position;
}

MouseEvent::Key MouseEvent::getKey() const
{
	return key;
}

MouseEvent::Type MouseEvent::getType() const
{
	return type;
}