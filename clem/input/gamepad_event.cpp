// Copyright 2020 SMS
// License(Apache-2.0)
// ÊÖ±úÊÂ¼þ

#include "gamepad_event.h"
#include <cassert>

GamepadEvent::GamepadEvent(SubType, Gamepad*, short key, bool status)
		: Event(Event::Type::gamepad), subType(subType), gamepad(gamepad),
			keyCode(key), status(status)
{
}

GamepadEvent::GamepadEvent(SubType, Gamepad*, short key, float value)
		: Event(Event::Type::gamepad), subType(subType), gamepad(gamepad),
			keyCode(key), value(value)
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
	return status;
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
