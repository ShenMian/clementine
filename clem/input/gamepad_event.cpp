// Copyright 2020 SMS
// License(Apache-2.0)
// ÊÖ±úÊÂ¼ş

#include "gamepad_event.h"

GamepadEvent::GamepadEvent(SubType subType, Gamepad* gamepad)
		: Event(Event::Type::gamepad), subType(subType), gamepad(gamepad)
{
}

SubType GamepadEvent::getSubType() const
{
	return subType;
}

Gamepad* GamepadEvent::getGamepad() const
{
	return gamepad;
}
