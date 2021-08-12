// Copyright 2021 SMS
// License(Apache-2.0)

#include "DirectionLight.h"

namespace clem
{

void DirectionLight::setDirection(const Vector3& dir)
{
}

Light::Type DirectionLight::getType() const
{
    return Type::Directional;
}

} // namespace clem