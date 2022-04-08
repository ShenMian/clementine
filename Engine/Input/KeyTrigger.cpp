// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "KeyTrigger.h"

namespace input
{

KeyTrigger::KeyTrigger(Key key)
	: key(key)
{
}

bool KeyTrigger::isActuated()
{
	return Input::isPressed(key);
}

}
