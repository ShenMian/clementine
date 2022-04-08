// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Mapping.h"
#include "Trigger.h"
#include <algorithm>

namespace input
{

void Mapping::update()
{
	for(auto& [trigger, action] : map)
	{
		if(trigger->isActuated())
			action();
	}
}

void Mapping::add(std::shared_ptr<Trigger> trigger, std::function<void()> action)
{
	map.emplace_back(trigger, action);
}

void Mapping::remove(std::shared_ptr<Trigger> trigger)
{
	map.erase(std::remove_if(map.begin(), map.end(), [&](auto& value) { return value.first == trigger; }));
}

}
