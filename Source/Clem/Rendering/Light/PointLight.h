// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Light.h"

namespace clem
{

/**
 * @brief 点光源.
 */
class PointLight : public Light
{
public:
    /**
     * @brief 设置光源坐标.
     *
     * @param pos 光源坐标.
     */
    void setPosition(const Vector3& pos);

    /**
     * @brief 获取光源坐标.
     */
    const Vector3& getPosition() const;

    Type getType() const override;

private:
    Vector3 position;

    float constant  = 1.0f;
    float linear    = 0.09f;
    float quadratic = 0.032f;
};

} // namespace clem