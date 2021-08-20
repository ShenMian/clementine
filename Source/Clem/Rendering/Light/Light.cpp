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
    this->ambient  = color;
    this->diffuse  = color;
    this->specular = color;
}

void Light::setColor(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
{
    this->ambient  = ambient;
    this->diffuse  = diffuse;
    this->specular = specular;
}

void Light::getColor(Vector3* ambient, Vector3* diffuse, Vector3* specular) const
{
    if(ambient)
        *ambient  = this->ambient;
    if(diffuse)
        *diffuse  = this->diffuse;
    if(specular)
        *specular = this->specular;
}

} // namespace clem