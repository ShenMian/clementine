// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CIRCLE_COLLIDER_H_
#define CLEM_CIRCLE_COLLIDER_H_

#include "collider.h"

/**
 * @addtogroup physics
 * @{
 */

/**
 * 圆形碰撞体.
 */
class CircleCollider : public Collider
{
public:
	CircleCollider();
	explicit CircleCollider(float radius);

	bool collides(const Collider& other) const override;

	void  setRadius(float);
	float getRadius() const;

private:
	float radius;
};

/**
 * end of physics group
 * @}
 */

#endif // !CLEM_CIRCLE_COLLIDER_H_
