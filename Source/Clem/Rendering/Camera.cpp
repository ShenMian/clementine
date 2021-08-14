﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Camera.h"

namespace clem
{

void Camera::lookAt(const Vector3& pos, const Vector3& up)
{
    ;
}

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
    dirty = true;
    if(dirty)
    {
        // viewProjection = projection * view.getInversed();
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