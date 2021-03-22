﻿// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_RIGIDBODY_H_
#define CLEM_COMPONENT_RIGIDBODY_H_

#include "Clem/Component/Component.h"
#include "Clem/Math/Vec2.h"

class Rigidbody : public Component
{
public:
	Vec2 velocity;
	Vec2 acceleration;
};

#endif // !CLEM_COMPONENT_RIGIDBODY_H_
