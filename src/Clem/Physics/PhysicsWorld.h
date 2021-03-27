// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Vector2.h"
#include <vector>

/**
 * @addtogroup Physics
 * @{
 */

class PhysicsWorld
{
public:
	void update(float dt);

private:
	Vector2 gravity;
};

/**
 * end of Physics group
 * @}
 */
