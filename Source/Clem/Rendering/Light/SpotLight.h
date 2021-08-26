// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Light.h"

namespace clem
{

/**
 * @brief 投射光.
 */
class SpotLight : public Light
{
public:
    /**
     * @brief 设置光源光照方向.
     *
     * @param dir 光照方向.
     */
    void setDirection(const Vector3& dir);

    /**
     * @brief 获取光源光照方向.
     */
    const Vector3& getDirection() const;

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
    Vector3 direction = {0, 0, 1};
    Vector3 position;
};

} // namespace clem