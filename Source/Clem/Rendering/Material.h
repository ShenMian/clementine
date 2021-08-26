// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/TypeIndex.hpp"
#include "Rendering/Shader.h"
#include "Rendering/Texture2D.h"
#include <memory>

namespace clem
{

/**
 * @brief 材质.
 */
class Material
{
    CLEM_DECLARE_TYPE;

public:
    Material() = default;
    Material(std::shared_ptr<Shader> shader);

    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 emission;

    std::shared_ptr<Texture2D> albedo;
    std::shared_ptr<Texture2D> normal;
    std::shared_ptr<Texture2D> metallic;
    std::shared_ptr<Texture2D> roughness;
    std::shared_ptr<Texture2D> emissive;

    float shininess = 32.f;

    std::shared_ptr<Shader> shader;
};

CLEM_DEFINE_TYPE(Material);

} // namespace clem