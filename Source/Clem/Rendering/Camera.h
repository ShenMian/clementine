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
    void setPosition(const Point3& pos);

    const Matrix4& getView() const;
    const Matrix4& getProjection() const;

private:
    Matrix4 view;
    Matrix4 projection;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem