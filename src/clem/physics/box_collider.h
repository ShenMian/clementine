// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_BOX_COLLIDER_H_
#define CLEM_BOX_COLLIDER_H_

#include "collider.h"
#include "clem/type.h"

/**
 * @addtogroup physics
 * @{
 */

/**
 * 盒形碰撞体.
 */
class BoxCollider : public Collider
{
public:
	BoxCollider();
	explicit BoxCollider(Size size);

	bool collides(const Collider& other) const override;

	void setSize(Size);
	Size getSize() const;

	Rect getRect() const;

private:
  Size size;
};

/**
 * end of physics group
 * @}
 */

#endif // !CLEM_BOX_COLLIDER_H_
