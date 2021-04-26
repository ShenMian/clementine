﻿// Copyright 2021 SMS
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
	enum class Type
	{
		Dynamic,
		Kinematic,
		Static
	};

	Vector2 velocity;

	/**
	 * @brief 向刚体施加一个持续的力.
	 *
	 * @param force 施加的持续的力.
	 */
	void addForce(const Vector2& force);

	/**
	 * @brief 获取刚体收到的持续的力.
	 */
	const Vector2& getForce() const;

	/**
	 * @brief 设置加速度.
	 *
	 * @param acc 加速度.
	 */
	void setAcceleration(const Vector2& acc);

	/**
	 * @brief 获取加速度.
	 */
	Vector2 getAcceleration() const;

	/**
	 * @brief 设置质量.
	 *
	 * @param m 质量, kg;
	 */
	void setMass(float m);

	/**
	 * @brief 获取质量.
	 */
	float getMass() const;

	/**
	 * @brief 设置类型.
	 */
	void setType(Type);

	/**
	 * @brief 获取类型.
	 */
	Type getType() const;

	void setPosition(const Point2&);

	Point2 getPosition();

	/**
	 * @brief 设置所属的实体.
	 *
	 * @param e 所属的实体;
	 */
	void setEntity(const Entity& e);

	/**
	 * @brief 获取所属的实体.
	 */
	Entity& getEntity();

private:
	Vector2 force;
	float   mass = 1.0f;
	Type    type = Type::Dynamic;
	Entity  entity;
};

template <>
inline void Scene::onComponentAdded(Entity e, Rigidbody& b)
{
	b.setEntity(e);
	physicsWorld.addBody(b);
}

template <>
inline void Scene::onComponentRemoved(Entity e, Rigidbody& b)
{
	physicsWorld.removeBody(b);
}

/**
 * end of Physics group
 * @}
 */
} // namespace clem
