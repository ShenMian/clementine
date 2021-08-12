// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Light.h"

namespace clem
{

class DirectionLight : public Light
{
public:
    /**
     * @brief 构造函数.
     * 
     * @param dir 光照方向.
     * @param color 光源颜色.
     */
    DirectionLight(const Vector3& dir, const Vector3& color);

    /**
     * @brief 设置光照方向.
     * 
     * @param dir 光照方向.
     */
    void setDirection(const Vector3& dir);

    /**
     * @brief 获取光照方向.
     */
    const Vector3& getDirection() const;

    Type getType() const override;

private:
    Vector3 direction;
};

} // namespace clem