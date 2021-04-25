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
void Transform::setDirty(bool d)
{
	dirty = d;
}

bool Transform::isDirty() const
{
	return dirty;
}

void Transform::setParent(Transform* p)
{
	ASSERT_TRUE(p != this, "parent can't be itself");
	parent = p;
}

Transform* Transform::getParent() const
{
	return parent;
}
} // namespace clem