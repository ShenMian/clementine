// Copyright 2021 SMS
// License(Apache-2.0)

#include "Light.h"

namespace clem
{

void Light::setIntesity(float intesity)
{
    this->intesity = intesity;
}

float Light::getIntesity() const
{
    return intesity;
}

void Light::setColor(const Vector3& color)
{
    this->color = color;
}

Vector3 Light::getColor() const
{
    return color;
}

} // namespace clem