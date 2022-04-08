// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace input
{

class Trigger;

class Mapping
{
public:
	void update();

	void add(std::shared_ptr<Trigger> trigger, std::function<void()> action);
	void remove(std::shared_ptr<Trigger> trigger);

private:
	std::vector<std::pair<std::shared_ptr<Trigger>, std::function<void()>>> map;
};

}
