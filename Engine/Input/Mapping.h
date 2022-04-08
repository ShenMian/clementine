// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <functional>
#include <map>
#include <vector>

namespace input
{

class Trigger;

class Mapping
{
public:
	void update();

	void add(Trigger& trigger, std::function<void()> action);
	void remove(Trigger& trigger);

private:
	std::vector<std::pair<Trigger*, std::function<void()>>> map;
};

}
