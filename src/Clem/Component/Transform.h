// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_TRANSFORM_H_
#define CLEM_COMPONENT_TRANSFORM_H_

#include "Clem/Component/Component.h"
#include "Clem/Core/Math/Vector2f.h"

class Transform : public Component
{
public:
	Vector2f position;
	Vector2f rotation;
};

#endif // !CLEM_COMPONENT_TRANSFORM_H_
