// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/TypeIndex.hpp"
#include "Rendering/Shader.h"
#include <memory>

namespace clem
{

class Material
{
    CLEM_DECLARE_TYPE;

public:
    Material();
    Material(float ambient, float diffuse, float specular, float shininess, std::shared_ptr<Shader> shader = nullptr);
    Material(
        Vector3                 ambient,
        Vector3                 diffuse,
        Vector3                 specular,
        float                   shininess,
        std::shared_ptr<Shader> shader = nullptr);

    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float   shininess;

    std::shared_ptr<Shader> shader;

    static const Material silver; // 0.19225, 0.50754, 0.508273, 51.2f
    static const Material chrome; // 0.25,    0.4,     0.774597, 76.8f};
};

CLEM_DEFINE_TYPE(Material);

} // namespace clem