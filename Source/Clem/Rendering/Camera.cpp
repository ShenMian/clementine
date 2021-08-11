// Copyright 2021 SMS
// License(Apache-2.0)

#include "Camera.h"

namespace clem
{

void Camera::setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    projection = Matrix4::createPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    dirty      = true;
    type       = Type::Perspective;
}

void Camera::setOrthographic(float l, float r, float b, float t,
                             float n, float f)
{
    projection = Matrix4::createOrthographicOffCenter(l, r, b, t, n, f);
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

const Matrix4& Camera::getViewProjectionMatrix()
{
    if(dirty)
    {
        viewProjection = view * projection; // FIXME
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