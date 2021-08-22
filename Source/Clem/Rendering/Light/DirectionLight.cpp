// Copyright 2021 SMS
// License(Apache-2.0)

#include "DirectionLight.h"

namespace clem
{

DirectionLight::DirectionLight(const Vector3& dir, const Vector3& color)
    : direction(dir)
{
    setColor(color);
}

void DirectionLight::setDirection(const Vector3& dir)
{
    direction = dir;
}

const Vector3& DirectionLight::getDirection() const
{
    return direction;
}

Light::Type DirectionLight::getType() const
{
    return Type::Directional;
}

} // namespace clem