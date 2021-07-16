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
 * @brief 圆形碰撞体.
 */
class CircleCollider : public Collider
{
public:
	CircleCollider() = default;
	explicit CircleCollider(float radius);

	/**
	 * @brief 设置半径
	 *
	 * @param r 半径
	 */
	void setRadius(float r);

	/**
	 * @brief 获取半径
	 *
	 * @return float 半径
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
