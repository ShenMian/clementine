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
	if(dirty)
	{
		if(parent)
			worldPosition = parent->getWorldPosition() + position;
		else
			worldPosition = position;
		dirty = false;
	}
	return worldPosition;
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
	dirty  = true;
	parent = p;
}

Transform* Transform::getParent() const
{
	return parent;
}
} // namespace clem