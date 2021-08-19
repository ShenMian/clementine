// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "Rendering/Texture2D.h"
#include <memory>
#include <vector>

namespace clem
{

class FrameBuffer
{
public:
    static std::shared_ptr<FrameBuffer> create(Size2 size, int samples = 1);

    virtual std::shared_ptr<Texture2D> getColorAttachment(int index) = 0;
    virtual std::shared_ptr<Texture2D> getDepthAttachment() = 0;

    virtual void bind()   = 0;
    virtual void unbind() = 0;

protected:
    std::vector<std::shared_ptr<Texture2D>> colorAttachment;
    std::shared_ptr<Texture2D>              depthAttachment;
};

} // namespace clem