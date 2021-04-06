// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Components/Component.h"
#include "Clem/Core/Math/Math.h"

namespace clem
{
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

	/**
	 * @brief 设置质量.
	 *
	 * @param m 质量, kg;
	 */
	void setMass(float m);

private:
	float   mass = 1.0f;
	Vector2 acceleration;
};

/**
 * end of Physics group
 * @}
 */
} // namespace clem
