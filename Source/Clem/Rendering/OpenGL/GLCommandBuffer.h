// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/CommandBuffer.h"

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class GLCommandBuffer : public CommandBuffer
{
public:
    void begin() override;
    void end() override;
    void setViewport(int x, int y, int width, int height) override;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem