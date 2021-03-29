// Copyright 2021 SMS
// License(Apache-2.0)

#include "Keyboard.h"
#include <cassert>

std::unordered_map<Keyboard::Key, bool> Keyboard::states;

bool Keyboard::getKeyState(Key k)
{
	assert(states.find(k) != states.end());
	return states[k];
}

void Keyboard::setKeyState(Key k, bool s)
{
	states[k] = s;
}
