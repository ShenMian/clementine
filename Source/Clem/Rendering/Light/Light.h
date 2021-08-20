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
        Spot         // 投射光
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
     * @brief 设置光源颜色.
     *
     * @param color 光源颜色.
     */
    void setColor(const Vector3& color);

    /**
     * @brief 设置光源颜色.
     *
     * @param ambient  环境光颜色.
     * @param diffuse  漫反射光颜色.
     * @param specular 镜面反射光颜色.
     */
    void setColor(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular = Vector3::unit);

    /**
     * @brief 获取光源颜色.
     */
    void getColor(Vector3* ambient, Vector3* diffuse, Vector3* specular) const;

    /**
     * @brief 获取光源类型.
     */
    virtual Type getType() const = 0;

protected:
    Vector3 ambient  = Vector3(1.f, 1.f, 1.f);
    Vector3 diffuse  = Vector3(1.f, 1.f, 1.f);
    Vector3 specular = Vector3(1.f, 1.f, 1.f);

    float intesity = 1;
};

} // namespace clem