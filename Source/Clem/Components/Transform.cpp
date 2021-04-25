// Copyright 2021 SMS
// License(Apache-2.0)

#include "Transform.h"
#include "Clem/Assert.h"

namespace clem
{
void Transform::setPosition(const Point2& p)
{
	dirty    = true;
	position = p;
}

Point2 Transform::getPosition() const
{
	return position;
}

Point2 Transform::getWorldPosition()
{
	ASSERT_TRUE(parent != this, "");
	if(parent && dirty)
	{
		worldPosition = parent->getWorldPosition() + position;
		dirty         = false;
		return worldPosition;
	}
	else
		return position;
}
} // namespace clem