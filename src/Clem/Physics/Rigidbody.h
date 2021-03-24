// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_RIGIDBODY_H_
#define CLEM_COMPONENT_RIGIDBODY_H_

#include "Clem/Component/Component.h"
#include "Clem/Core/Math/Vec2.h"

class Rigidbody : public Component
{
public:
	Vec2<float> velocity;
	Vec2<float> acceleration;
};

#endif // !CLEM_COMPONENT_RIGIDBODY_H_
