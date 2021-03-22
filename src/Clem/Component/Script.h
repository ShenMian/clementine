// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_SCRIPT_H_
#define CLEM_COMPONENT_SCRIPT_H_

#include "Component.h"
#include <functional>

class Script : public Component
{
public:
	std::function<void(float)> onUpdate;

	Script() = default;
};

#endif // !CLEM_COMPONENT_SCRIPT_H_
