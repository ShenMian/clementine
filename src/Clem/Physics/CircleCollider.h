// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_PHYSICS_CIRCLE_COLLIDER_H_
#define CLEM_PHYSICS_CIRCLE_COLLIDER_H_

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

#endif // !CLEM_PHYSICS_CIRCLE_COLLIDER_H_
