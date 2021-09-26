// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Material.h"

namespace clem
{

Material::Material()
    : shader(Shader::get("forward"))
{
}

Material::Material(std::shared_ptr<Shader> shader)
    : shader(shader)
{
}

} // namespace clem