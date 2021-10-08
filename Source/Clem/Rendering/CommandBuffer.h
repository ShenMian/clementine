// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class CommandBuffer
{
public:
    static std::shared_ptr<CommandBuffer> create();

    virtual void begin()                                          = 0;
    virtual void end()                                            = 0;
    virtual void setViewport(int x, int y, int width, int height) = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem