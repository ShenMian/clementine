// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Rect2.h"
#include "Clem/Core/Math/Vector2.h"
#include "Collider.h"

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

	void  setSize(Size2);
	Size2 getSize() const;

	Rect2 getRect() const;

private:
	Size2 size;
};

/**
 * end of Physics group
 * @}
 */