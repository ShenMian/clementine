// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"

namespace clem
{

/**
 * @addtogroup Physics
 * @{
 */

/**
 * @brief 碰撞体.
 */
class Collider
{
public:
    Collider() = default;

    /**
	 * @brief 设置偏移量.
	 */
    void setOffset(Point3 offset);

    /**
	 * @brief 获取偏移量.
	 */
    const Point3& getOffset() const;

    /**
	 * @brief 检测是否与指定点相交.
	 */
    // virtual bool intersect(const Point3& point) const = 0;

protected:
    Point3 offset;
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem
