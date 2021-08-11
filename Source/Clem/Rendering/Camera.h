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
    enum class Type
    {
        Perspective,
        Orthographic
    };

    void setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    void setOrthographic(float left, float right, float bottom, float top,
                         float zNearPlane, float zFarPlane);

    const Matrix4& getViewMatrix() const;
    const Matrix4& getProjectionMatrix() const;
    const Matrix4& getViewProjectionMatrix();

    void setDeepth(int deepth);
    int  getDeepth() const;

    Type getType() const;

    Matrix4 view;

private:
    Matrix4 projection;
    Matrix4 viewProjection;
    bool    dirty = true;
    Type    type;
    int     deepth;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem