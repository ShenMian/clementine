// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/TypeIndex.hpp"
#include "Rendering/Shader.h"
#include "Rendering/Texture2D.h"
#include <memory>

// TODO: 重命名并减少材质数量到合适

namespace clem
{

/**
 * @brief 材质.
 */
class Material
{
    CLEM_DECLARE_TYPE;

public:
    Material();
    Material(std::shared_ptr<Shader> shader);

    std::string             name;
    std::shared_ptr<Shader> shader;

    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 emission;
    float   shininess = 0.f;

    std::shared_ptr<Texture2D> albedo;    // Kd
    std::shared_ptr<Texture2D> metallic;  // Ks
    std::shared_ptr<Texture2D> roughness; // Ns
    std::shared_ptr<Texture2D> ao;        // Ka
    std::shared_ptr<Texture2D> emissive;  // Ke
    std::shared_ptr<Texture2D> normal;
};

CLEM_DEFINE_TYPE(Material);

} // namespace clem