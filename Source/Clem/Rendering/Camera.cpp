// Copyright 2021 SMS
// License(Apache-2.0)

#include "Camera.h"

namespace clem
{

void Camera::setPosition(const Point3& pos)
{
}

const Matrix4& Camera::getView() const
{
    return view;
}

const Matrix4& Camera::getProjection() const
{
    return projection;
}

} // namespace clem