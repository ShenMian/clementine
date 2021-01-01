// Copyright 2020 SMS
// License(Apache-2.0)
// ÊÖ±úÊÂ¼ş

#include "gamepad_event.h"
#include <cassert>

GamepadEvent::GamepadEvent(SubType subType, Gamepad* gamepad)
		: Event(Event::Type::gamepad), subType(subType), gamepad(gamepad)
{
}

GamepadEvent::SubType GamepadEvent::getSubType() const
{
	return subType;
}

short GamepadEvent::getKeyCode() const
{
	return keyCode;
}

bool GamepadEvent::getKeyStatus() const
{
	assert(subType == SubType::button_status_changed);
	return keyStatus;
}

float GamepadEvent::getValue() const
{
	assert(subType == SubType::axis_status_changed);
	return value;
}

Gamepad* GamepadEvent::getGamepad() const
{
	return gamepad;
}
