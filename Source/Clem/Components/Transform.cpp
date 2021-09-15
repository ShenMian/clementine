// Copyright 2021 SMS
// License(Apache-2.0)

#include "Transform.h"
#include "Core/Assert.hpp"

namespace clem
{

Transform::operator Matrix4()
{
    Matrix4 mat;

    const float c3 = std::cos(radians(rotation.z));
    const float s3 = std::sin(radians(rotation.z));
    const float c2 = std::cos(radians(rotation.x));
    const float s2 = std::sin(radians(rotation.x));
    const float c1 = std::cos(radians(rotation.y));
    const float s1 = std::sin(radians(rotation.y));

    mat[0][0] = scale.x * (c1 * c3 + s1 * s2 * s3);
    mat[0][1] = scale.x * (c2 * s3);
    mat[0][2] = scale.x * (c1 * s2 * s3 - c3 * s1);
    mat[0][3] = 0.0f;

    mat[1][0] = scale.y * (c3 * s1 * s2 - c1 * s3);
    mat[1][1] = scale.y * (c2 * c3);
    mat[1][2] = scale.y * (c1 * c3 * s2 + s1 * s3);
    mat[1][3] = 0.0f;

    mat[2][0] = scale.z * (c2 * s1);
    mat[2][1] = scale.z * (-s2);
    mat[2][2] = scale.z * (c1 * c2);
    mat[2][3] = 0.0f;

    mat[3][0] = translation.x;
    mat[3][1] = translation.y;
    mat[3][2] = translation.z;
    mat[3][3] = 1.0f;

    return mat;
}

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
	// FIXME: 实现不正确
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