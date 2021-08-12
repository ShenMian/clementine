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

void Light::setPosition(const Vector3& pos)
{
    position = pos;
}

const Vector3& Light::getPosition() const
{
    return position;
}

void Light::setColor(const Vector3& color)
{
    this->color = color;
}

const Vector3& Light::getColor() const
{
    return color;
}

} // namespace clem