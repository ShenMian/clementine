// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_TRANSFORM_H_
#define CLEM_COMPONENT_TRANSFORM_H_

#include "Clem/Component/Component.h"
#include "Clem/Math/Vec2.h"

class Transform : public Component
{
public:
	Vec2 position;
	Vec2 rotation;
};

#endif // !CLEM_COMPONENT_TRANSFORM_H_