// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/ECS.h"

namespace clem
{

/**
 * @addtogroup Physics
 * @{
 */

/**
 * @brief 刚体.
 */
class Rigidbody
{
    CLEM_DECLARE_TYPE;

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

    float mass = 1.f;
    Type  type = Type::Kinematic;

private:
    Vector2 force;
};

CLEM_DEFINE_TYPE(Rigidbody);

/**
 * end of Physics group
 * @}
 */

} // namespace clem
