// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Core.h"
#include "ECS/ECS.h"
namespace clem
{

/**
 * @addtogroup ECS
 * @{
 */

/**
 * @brief 系统. 所有系统继承自该类.
 */
class System
{
public:
    /**
     * @brief 更新.
     * 
     * @param dt 时间.
     * @param reg 注册器.
     */
    virtual void update(Time dt, Registry& reg) = 0;

    virtual void init();
    virtual void deinit();
};

/**
 * end of ECS group
 * @}
 */

} // namespace clem
