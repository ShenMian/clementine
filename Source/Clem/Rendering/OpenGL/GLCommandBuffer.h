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
    
    void clear(uint8_t flags) override;
    void setClearColor(const Vector4& color) override;
    void setClearDepth(float depth) override;

    void setViewport(int x, int y, int width, int height) override;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem