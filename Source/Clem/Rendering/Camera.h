// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "Components/Transform.h"
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

    // void setDirection(const Vector3& pos, const Vector3& dir, const Vector3& up = -Vector3::unit_y);
    // void setViewYXZ(const Vector3& pos, const Vector3& rotation);
    // void lookAt(const Vector3& pos, const Vector3& target, const Vector3& up = -Vector3::unit_y);

    void setPerspective(float yFOV, float aspectRatio, float nearPlane, float farPlane);
    void setOrthographic(float width, float height, float nearPlane, float farPlane);

    Matrix4 getViewMatrix();
    const Matrix4& getProjectionMatrix() const;
    const Matrix4& getViewProjectionMatrix();

    void setDeepth(int deepth);
    int  getDeepth() const;

    Type getType() const;

    Transform view;

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