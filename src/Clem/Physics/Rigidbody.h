// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Components/Component.h"
#include "Clem/Core/Math/Math.h"
#include "Clem/Scene/Entity.h"

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
	 * @brief 向刚体施加一个持续的力.
	 *
	 * @param force 施加的持续的力.
	 */
	void addForce(const Vector2& force);

	/**
	 * @brief 设置加速度.
	 *
	 * @param force 加速度.
	 */
	void setAcceleration(const Vector2& acc);

	/**
	 * @brief 设置质量.
	 *
	 * @param m 质量, kg;
	 */
	void setMass(float m);

	/**
	 * @brief 设置所属的实体.
	 *
	 * @param e 所属的实体;
	 */
	void setEntity(const Entity& e);

	/**
	 * @brief 获取所属的实体.
	 */
	const Entity& getEntity() const;

private:
	float   mass = 1.0f;
	Vector2 acceleration;
	Entity  entity;
};

/**
 * end of Physics group
 * @}
 */
} // namespace clem
