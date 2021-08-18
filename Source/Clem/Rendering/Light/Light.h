// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"

namespace clem
{

class Light
{
public:
    enum class Type
    {
        Directional, // 平行光
        Point,       // 点光源
        Spot,        // 投射光
        Ambient      // 环境光
    };

    /**
     * @brief 设置光照强度.
     *
     * @param intesity 光照强度.
     */
    void setIntesity(float intesity);

    /**
     * @brief 获取光照强度.
     */
    float getIntesity() const;

    /**
     * @brief 设置光源位置.
     *
     * @param pos 光源位置.
     */
    void setPosition(const Vector3& pos);

    /**
     * @brief 获取光源位置.
     */
    const Vector3& getPosition() const;

    /**
     * @brief 设置光源颜色.
     *
     * @param color 光源颜色.
     */
    void setColor(const Vector3& color);

    /**
     * @brief 获取光源颜色.
     */
    const Vector3& getColor() const;

    /**
     * @brief 获取光源类型.
     */
    virtual Type getType() const = 0;

protected:
    Vector3 position;
    Vector3 color    = Vector3(1.f, 1.f, 1.f);
    float   intesity = 1;
};

} // namespace clem