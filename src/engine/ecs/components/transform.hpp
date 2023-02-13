// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/type_index.hpp"
#include "ecs/component.hpp"

namespace ecs
{

struct Transform : public Component
{
	DECLARE_TYPE
};

} // namespace ecs
