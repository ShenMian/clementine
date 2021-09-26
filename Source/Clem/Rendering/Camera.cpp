// Copyright 2021 SMS
// License(Apache-2.0)

#include "Camera.h"
#include "Core/Assert.hpp"

namespace clem
{

/*
void Camera::setDirection(const Vector3& pos, const Vector3& dir, const Vector3& up)
{
    // 构建三个相互垂直且长度为一的向量, 其中 w 与 dir 方向相同.
    const Vector3 w = dir.getNormalized();
    const Vector3 u = w.cross(up).getNormalized();
    const Vector3 v = w.cross(u);

    view       = Matrix4::identity;
    view[0][0] = u.x;
    view[1][0] = u.y;
    view[2][0] = u.z;
    view[0][1] = v.x;
    view[1][1] = v.y;
    view[2][1] = v.z;
    view[0][2] = w.x;
    view[1][2] = w.y;
    view[2][2] = w.z;
    view[3][0] = -u.dot(pos);
    view[3][1] = -v.dot(pos);
    view[3][2] = -w.dot(pos);
}

void Camera::setViewYXZ(const Vector3& pos, const Vector3& rotation)
{
    const float   c3 = std::cos(rotation.z);
    const float   s3 = std::sin(rotation.z);
    const float   c2 = std::cos(rotation.x);
    const float   s2 = std::sin(rotation.x);
    const float   c1 = std::cos(rotation.y);
    const float   s1 = std::sin(rotation.y);
    const Vector3 u(c1 * c3 + s1 * s2 * s3, c2 * s3, c1 * s2 * s3 - c3 * s1);
    const Vector3 v(c3 * s1 * s2 - c1 * s3, c2 * c3, c1 * c3 * s2 + s1 * s3);
    const Vector3 w(c2 * s1, -s2, c1 * c2);

    view       = Matrix4::identity;
    view[0][0] = u.x;
    view[1][0] = u.y;
    view[2][0] = u.z;
    view[0][1] = v.x;
    view[1][1] = v.y;
    view[2][1] = v.z;
    view[0][2] = w.x;
    view[1][2] = w.y;
    view[2][2] = w.z;
    view[3][0] = -u.dot(pos);
    view[3][1] = -v.dot(pos);
    view[3][2] = -w.dot(pos);
}

void Camera::lookAt(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    setDirection(pos, target - pos, up);
}

*/

void Camera::setPerspective(float yFOV, float aspectRatio, float n, float f)
{
    projection = Matrix4::createPerspective(yFOV, aspectRatio, n, f);
    dirty      = true;
    type       = Type::Perspective;
}

void Camera::setOrthographic(float w, float h, float n, float f)
{
    projection = Matrix4::createOrthographic(w, h, n, f);
    dirty      = true;
    type       = Type::Orthographic;
}

Matrix4 Camera::getViewMatrix()
{
#if 0
    return view_;
#else
    return static_cast<Matrix4>(view);
#endif
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
        viewProjection = static_cast<Matrix4>(view) * projection;
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