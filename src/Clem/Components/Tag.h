// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_TAG_H_
#define CLEM_COMPONENT_TAG_H_

#include "Clem/Core/Math/Math.h"
#include "Component.h"

#include <string>

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

#endif // !CLEM_COMPONENT_TAG_H_
