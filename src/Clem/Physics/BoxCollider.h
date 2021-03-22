// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_BOX_COLLIDER_H_
#define CLEM_BOX_COLLIDER_H_

#include "collider.h"
#include "Clem/Math/Vec2.h"
#include "Clem/Math/Rect.h"

/**
 * @addtogroup Physics
 * @{
 */

/**
 * 盒形碰撞体.
 */
class BoxCollider : public Collider
{
public:
	BoxCollider() = default;
	explicit BoxCollider(Size size);

	void setSize(Size);
	Size getSize() const;

	Rect getRect() const;

private:
  Size size;
};

/**
 * end of Physics group
 * @}
 */

#endif // !CLEM_BOX_COLLIDER_H_
