// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Component.h"

#include <string>

namespace clem
{

/**
 * @brief 标签组件.
 */
class Tag : public Component
{
public:
	std::string string;

	Tag() = default;
	Tag(const std::string& tag)
			: string(tag)
	{
	}
};

} // namespace clem
