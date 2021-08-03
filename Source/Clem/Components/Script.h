// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Core.h"
#include "ECS/ECS.h"
#include <functional>

namespace clem
{
/**
 * @brief 脚本组件.
 */
class Script
{
	CLEM_DECLARE_TYPE;

public:
	Script() = default;

	virtual void update(float dt);

	std::function<void(Time)> onUpdate;
};

CLEM_DEFINE_TYPE(Script);

} // namespace clem
