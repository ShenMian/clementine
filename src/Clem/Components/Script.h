// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_SCRIPT_H_
#define CLEM_COMPONENT_SCRIPT_H_

#include "Component.h"
#include <functional>

class Script : public Component
{
public:
	Script() = default;
	
	virtual void update(float dt);

	std::function<void(float)> onUpdate = std::bind(&Script::update, this, std::placeholders::_1);
};

#endif // !CLEM_COMPONENT_SCRIPT_H_
