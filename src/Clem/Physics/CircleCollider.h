// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Collider.h"

/**
 * @addtogroup Physics
 * @{
 */

/**
 * 圆形碰撞体.
 */
class CircleCollider : public Collider
{
public:
	CircleCollider() = default;
	explicit CircleCollider(float radius);

	void  setRadius(float);
	float getRadius() const;

private:
	float radius = 0;
};

/**
 * end of Physics group
 * @}
 */
