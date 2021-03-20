// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_TAG_H_
#define CLEM_COMPONENT_TAG_H_

#include "Clem/Component/Component.h"
#include "Clem/Math/Vec2.h"

#include <string>

class Tag : public Component
{
public:
	std::string tag;

	Tag() = default;
	Tag(const std::string& tag)
			: tag(tag)
	{
	}
};

#endif // !CLEM_COMPONENT_TAG_H_