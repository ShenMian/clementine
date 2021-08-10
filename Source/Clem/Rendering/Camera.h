// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <memory>
#include <string>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Camera
{
public:
    Matrix4 view;
    Matrix4 projection;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem