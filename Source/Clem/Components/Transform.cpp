// Copyright 2021 SMS
// License(Apache-2.0)

#include "Transform.h"
#include "Assert.hpp"

namespace clem
{

Matrix4 Transform::getModelMatrix()
{
    if(isDirty())
    {
        model = Matrix4::identity;
        model.translate(translation);
        model.rotateX(radians(rotation.x));
        model.rotateY(radians(rotation.y));
        model.rotateZ(radians(rotation.z));
        model.scale(scale);

        lastTranslation = translation;
        lastRotation    = rotation;
        lastScale       = scale;
    }
    return model;
}

bool Transform::isDirty() const
{
    return lastTranslation != translation || lastRotation != rotation || lastScale != scale;
}

/*
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
	Assert::isTrue(p != this, "parent can't be itself");
	dirty  = true;
	parent = p;
}

Transform* Transform::getParent() const
{
	return parent;
}
*/

} // namespace clem