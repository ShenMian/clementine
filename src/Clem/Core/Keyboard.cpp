// Copyright 2021 SMS
// License(Apache-2.0)

#include "Keyboard.h"
#include <cassert>

namespace clem
{
std::unordered_map<Keyboard::Key, bool> Keyboard::states;

bool Keyboard::getKeyState(Key k)
{
	if(states.find(k) != states.end())
		return states[k];
	else
		return false;
}

void Keyboard::setKeyState(Key k, bool s)
{
	states[k] = s;
}
} // namespace clem