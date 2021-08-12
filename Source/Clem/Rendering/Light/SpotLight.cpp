// Copyright 2021 SMS
// License(Apache-2.0)

#include "SpotLight.h"

namespace clem
{

void SpotLight::setDirection(const Vector3& dir)
{
}

Light::Type SpotLight::getType() const
{
    return Type::Spot;
}

} // namespace clem