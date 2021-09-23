// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Collider.h"

namespace clem
{

/**
 * @addtogroup Physics
 * @{
 */

/**
 * @brief 球形碰撞体.
 */
class SphereCollider : public Collider
{
public:
    SphereCollider() = default;

    /**
	 * @brief 构造函数.
	 *
	 * @param radius 半径.
	 */
    explicit SphereCollider(float radius);

    /**
	 * @brief 设置半径.
	 *
	 * @param radius 半径.
	 */
    void setRadius(float radius);

    /**
	 * @brief 获取半径.
	 */
    float getRadius() const;

private:
    float radius = 0;
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem
