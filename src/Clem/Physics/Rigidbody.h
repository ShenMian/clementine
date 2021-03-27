// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Component/Component.h"
#include "Clem/Core/Math/Math.h"

/**
 * @addtogroup Physics
 * @{
 */

/**
 * @brief 刚体.
 */
class Rigidbody : public Component
{
public:
	Vector2 velocity;

	/**
	 * @brief 向刚体施加一个力.
	 *
	 * @param force 施加的力.
	 */
	void addForce(const Vector2& force);

private:
	float   mass = 0.0f;
	Vector2 acceleration;
};

/**
 * end of Physics group
 * @}
 */
