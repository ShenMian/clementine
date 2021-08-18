// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"

namespace clem
{

class Material
{
public:
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float   shininess;

    const static Material silver;
    const static Material chrome;
};

} // namespace clem