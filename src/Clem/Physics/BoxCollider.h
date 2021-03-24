﻿// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_BOX_COLLIDER_H_
#define CLEM_BOX_COLLIDER_H_

#include "Collider.h"
#include "Clem/Core/Math/Vector2f.h"
#include "Clem/Core/Math/Rect2f.h"

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
	explicit BoxCollider(Size2 size);

	void setSize(Size2);
	Size2 getSize() const;

	Rect2 getRect() const;

private:
  Size2 size;
};

/**
 * end of Physics group
 * @}
 */

#endif // !CLEM_BOX_COLLIDER_H_
