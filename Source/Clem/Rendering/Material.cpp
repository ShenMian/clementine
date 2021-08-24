// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Material.h"

namespace clem
{

Material::Material(float shininess, std::shared_ptr<Shader> shader)
    : shininess(shininess), shader(shader)
{
}

} // namespace clem