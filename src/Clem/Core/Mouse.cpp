// Copyright 2021 SMS
// License(Apache-2.0)

#include "Mouse.h"
#include <cassert>

std::unordered_map<Mouse::Key, bool> Mouse::states;
Point2i                              Mouse::position;

bool Mouse::getKeyState(Key k)
{
	assert(states.find(k) != states.end());
	return states[k];
}

void Mouse::setKeyState(Key k, bool s)
{
	states[k] = s;
}

Point2i Mouse::getPosition()
{
	return position;
}

void Mouse::setPosition(Point2i p)
{
	position = p;
}
