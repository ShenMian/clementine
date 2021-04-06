// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Component.h"
#include <functional>

namespace clem
{

/**
 * @brief 脚本组件.
 */
class Script : public Component
{
public:
	Script() = default;

	virtual void update(float dt);

	std::function<void(float)> onUpdate;
};

} // namespace clem
