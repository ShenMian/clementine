// Copyright 2021 SMS
// License(Apache-2.0)

#include "PointLight.h"

namespace clem
{

void PointLight::setPosition(const Vector3& pos)
{
    position = pos;
}

const Vector3& PointLight::getPosition() const
{
    return position;
}

Light::Type PointLight::getType() const
{
    return Type::Point;
}

} // namespace clem