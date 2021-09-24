// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Components/Transform.h"
#include "Core/Math/Math.h"
#include <memory>
#include <string>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

/**
 * @brief 摄像机.
 */
class Camera
{
public:
    enum class Type
    {
        Perspective, // 透视投影
        Orthographic // 正交投影
    };

    // void setDirection(const Vector3& pos, const Vector3& dir, const Vector3& up = -Vector3::unit_y);
    // void setViewYXZ(const Vector3& pos, const Vector3& rotation);
    // void lookAt(const Vector3& pos, const Vector3& target, const Vector3& up = -Vector3::unit_y);

    /**
     * @brief 设置截头锥体观察体, 用于透视投影.
     *
     * @param yFOV        垂直视角范围, 单位: 弧度制.
     * @param aspectRatio 宽高比.
     * @param nearPlane   近平面 z 坐标.
     * @param farPlane    远平面 z 坐标.
     */
    void setPerspective(float yFOV, float aspectRatio, float nearPlane, float farPlane);

    /**
     * @brief 设置正投影观观察体, 用于正交投影.
     *
     * @param width     宽度.
     * @param height    高度.
     * @param nearPlane 近平面 z 坐标.
     * @param farPlane  远平面 z 坐标.
     */
    void setOrthographic(float width, float height, float nearPlane, float farPlane);

    Matrix4        getViewMatrix();
    const Matrix4& getProjectionMatrix() const;
    const Matrix4& getViewProjectionMatrix();

    void setDeepth(int deepth);
    int  getDeepth() const;

    /**
     * @brief 获取投影类型.
     */
    Type getType() const;

    Matrix4   view_;
    Transform view;

private:
    Matrix4 projection;
    Matrix4 viewProjection;
    bool    dirty  = true;
    Type    type   = Type::Perspective;
    int     deepth = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem