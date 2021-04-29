// Copyright 2021 SMS
// License(Apache-2.0)

#include "Transform.h"
#include "Clem/Assert.h"

namespace clem
{
void Transform::setPosition(const Point2& p)
{
	dirty = true;
	local = p;
}

Point2 Transform::getPosition() const
{
	return local;
}

Point2 Transform::getWorldPosition()
{
	// FIXME
	if(dirty)
	{
		if(parent)
			world = parent->getWorldPosition() + local;
		else
			world = local;
		dirty = false;
	}
	return world;
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