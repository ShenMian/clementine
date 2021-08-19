// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Material.h"

namespace clem
{

Material::Material()
{
    *this = Material::silver;
}

Material::Material(float ambient, float diffuse, float specular, float shininess, std::shared_ptr<Shader> shader)
    : Material(Vector3::unit * ambient, Vector3::unit * diffuse, Vector3::unit * specular, shininess, shader)
{
}

Material::Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, float shininess, std::shared_ptr<Shader> shader)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), shader(shader)
{
}

const Material Material::silver = {0.19225, 0.50754, 0.508273, 51.2f};
const Material Material::chrome = {0.25, 0.4, 0.774597, 76.8f};

} // namespace clem