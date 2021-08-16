// Copyright 2021 SMS
// License(Apache-2.0)

#include "Camera.h"
#include "Assert.hpp"

namespace clem
{

void Camera::setDirection(const Vector3& pos, const Vector3& dir, const Vector3& up)
{
    // 构建三个相互垂直且长度为一的向量, 其中 w 与 dir 方向相同.
    const Vector3 w = dir.getNormalized();
    const Vector3 u = w.cross(up).getNormalized();
    const Vector3 v = w.cross(u);

    view         = Matrix4::identity;
    view.m[0][0] = u.x;
    view.m[1][0] = u.y;
    view.m[2][0] = u.z;
    view.m[0][1] = v.x;
    view.m[1][1] = v.y;
    view.m[2][1] = v.z;
    view.m[0][2] = w.x;
    view.m[1][2] = w.y;
    view.m[2][2] = w.z;
    view.m[3][0] = -u.dot(pos);
    view.m[3][1] = -v.dot(pos);
    view.m[3][2] = -w.dot(pos);
}

void Camera::lookAt(const Vector3& pos, const Vector3& up)
{
    setDirection(view.translation(), pos - view.translation(), up);
}

void Camera::setPerspective(float yFOV, float aspectRatio, float n, float f)
{
    projection = Matrix4::createPerspective(yFOV, aspectRatio, n, f);
    dirty      = true;
    type       = Type::Perspective;
}

// FIXME: 结果不正确
void Camera::setOrthographic(float w, float h, float n, float f)
{
    projection = Matrix4::createOrthographic(w, h, n, f);
    dirty      = true;
    type       = Type::Orthographic;
}

const Matrix4& Camera::getViewMatrix() const
{
    return view;
}

const Matrix4& Camera::getProjectionMatrix() const
{
    return projection;
}

// FIXME: 结果不正确
const Matrix4& Camera::getViewProjectionMatrix()
{
    dirty = true;
    if(dirty)
    {
        viewProjection = view.getInversed() * projection;
        dirty          = false;
    }
    return viewProjection;
}

void Camera::setDeepth(int deepth)
{
    this->deepth = deepth;
}

int Camera::getDeepth() const
{
    return deepth;
}

Camera::Type Camera::getType() const
{
    return type;
}

} // namespace clem