// Copyright 2021 SMS
// License(Apache-2.0)

#include "Mouse.h"
#include <cassert>

namespace clem
{
std::unordered_map<Mouse::Key, bool> Mouse::states;
Point2                               Mouse::position;

bool Mouse::getKeyState(Key k)
{
	if(states.find(k) != states.end())
		return states[k];
	else
		return false;
}

void Mouse::setKeyState(Key k, bool s)
{
	states[k] = s;
}

Point2 Mouse::getPosition()
{
	return position;
}

void Mouse::setPosition(Point2 p)
{
	position = p;
}
} // namespace clem