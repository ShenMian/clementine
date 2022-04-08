// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "ChordTrigger.h"

namespace input
{

ChordTrigger::ChordTrigger(std::initializer_list<Key> keys)
	: keys(keys)
{
}

bool ChordTrigger::isActuated()
{
	for(auto key : keys)
		if(!Input::isPressed(key))
			return false;
	return true;
}

}
