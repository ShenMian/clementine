// Copyright 2021 SMS
// License(Apache-2.0)

#include "SpotLight.h"

namespace clem
{

void SpotLight::setDirection(const Vector3& dir)
{
    direction = dir.getNormalized();
}

const Vector3& SpotLight::getDirection() const
{
    return direction;
}

void SpotLight::setPosition(const Vector3& pos)
{
    position = pos;
}

const Vector3& SpotLight::getPosition() const
{
    return position;
}

Light::Type SpotLight::getType() const
{
    return Type::Spot;
}

} // namespace clem