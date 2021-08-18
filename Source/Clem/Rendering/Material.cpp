// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Material.h"

namespace clem
{

const Material Material::silver = {Vector3::unit * 0.19225, Vector3::unit * 0.50754, Vector3::unit * 0.508273, 51.2f};
const Material Material::chrome = {Vector3::unit * 0.25, Vector3::unit * 0.4, Vector3::unit * 0.774597, 76.8f};

} // namespace clem