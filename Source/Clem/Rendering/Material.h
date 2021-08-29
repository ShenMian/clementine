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
    struct Texture
    {
        std::shared_ptr<Texture2D> ambient;            // Ka
        std::shared_ptr<Texture2D> diffuse;            // Kd, albedo
        std::shared_ptr<Texture2D> specular;           // Ks
        std::shared_ptr<Texture2D> specular_highlight; // Ns
        std::shared_ptr<Texture2D> bump;
        std::shared_ptr<Texture2D> displacement;
        std::shared_ptr<Texture2D> alpha;
        std::shared_ptr<Texture2D> reflection;

        std::shared_ptr<Texture2D> roughness; // Pr
        std::shared_ptr<Texture2D> metallic;  // Pm
        std::shared_ptr<Texture2D> sheen;     // Ps
        std::shared_ptr<Texture2D> emissive;  // Ke
        std::shared_ptr<Texture2D> normal;
    };

    Material();
    Material(std::shared_ptr<Shader> shader);

    std::string             name;
    std::shared_ptr<Shader> shader;

    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 emission;
    float   shininess = 0.f;

    Texture tex;
};

CLEM_DEFINE_TYPE(Material);

} // namespace clem