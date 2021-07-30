// Copyright 2021 SMS
// License(Apache-2.0)

#include "Camera.h"

namespace clem
{

void Camera::setPosition(const Point3& pos)
{
	view.translate(pos);
}

const Matrix4& Camera::getViewProjection() const
{
	return viewProjection;
}

} // namespace clem