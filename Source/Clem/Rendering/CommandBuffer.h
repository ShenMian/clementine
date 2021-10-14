// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <cstddef>
#include <memory>
#include <vector>

namespace clem
{

class VertexBuffer;
class IndexBuffer;

/**
 * @addtogroup Rendering
 * @{
 */

class CommandBuffer
{
public:
    enum CleanFlags : uint8_t
    {
        Color   = (1 << 0),
        Depth   = (1 << 1),
        Stencil = (1 << 2)
    };

    static std::shared_ptr<CommandBuffer> create();

    virtual void begin() = 0;
    virtual void end()   = 0;

    // virtual void setVertexBuffer(VertexBuffer& buffer) = 0;
    // virtual void setIndexBuffer(IndexBuffer& buffer)   = 0;

    virtual void clear(uint8_t flags)                = 0;
    virtual void setClearColor(const Vector4& color) = 0;
    virtual void setClearDepth(float depth)          = 0;
    
    virtual void setViewport(int x, int y, int width, int height) = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem