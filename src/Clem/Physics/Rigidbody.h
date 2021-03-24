// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_RIGIDBODY_H_
#define CLEM_COMPONENT_RIGIDBODY_H_

#include "Clem/Component/Component.h"
#include "Clem/Core/Math/Vector2f.h"

class Rigidbody : public Component
{
public:
	Vector2f velocity;
	Vector2f acceleration;
};

#endif // !CLEM_COMPONENT_RIGIDBODY_H_
