// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/ECS/ECS.h"
#include <string>

namespace clem
{
/**
 * @brief 标签组件.
 */
class Tag
{
	CLEM_DECLARE_TYPE;

public:
	std::string str;

	Tag() = default;
	Tag(const std::string& tag)
			: str(tag)
	{
	}
};

CLEM_DEFINE_TYPE(Tag);

} // namespace clem
