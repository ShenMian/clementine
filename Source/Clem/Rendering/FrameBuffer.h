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
    using PixelFormat = Texture2D::Format;

    static std::shared_ptr<FrameBuffer> create(Size2 size, std::vector<PixelFormat> attachs = {PixelFormat::Auto}, int samples = 1);

    virtual std::shared_ptr<Texture2D> getColorAttachment(int index = 0)          = 0;
    virtual std::shared_ptr<Texture2D> getDepthAttachment()                       = 0;
    virtual void                       clearColorAttachment(int index, int value) = 0;

    virtual void read(int index, Vector2i pos, int& data) = 0;

    virtual void bind()   = 0;
    virtual void unbind() = 0;

protected:
    std::vector<std::shared_ptr<Texture2D>> colorAttachments;
    std::shared_ptr<Texture2D>              depthAttachments;
};

} // namespace clem