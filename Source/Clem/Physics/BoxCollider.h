// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Collider.h"
#include "Core/Math/Math.h"

namespace clem
{

/**
 * @addtogroup Physics
 * @{
 */

/**
 * @brief AABB 盒形碰撞体.
 */
class BoxCollider : public Collider
{
public:
    BoxCollider() = default;
    explicit BoxCollider(Size2 size);

    /**
	* @brief 设置大小
	*
	* @param size 大小
	*/
    void setSize(Size2 size);

    /**
    * @brief 获取大小
    *
    * @return Size2 大小
    */
    Size2 getSize() const;

private:
    Size2 size;
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem