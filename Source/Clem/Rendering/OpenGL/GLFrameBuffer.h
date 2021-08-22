// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/FrameBuffer.h"

namespace clem
{

class GLFrameBuffer : public FrameBuffer
{
public:
    using handle_type = unsigned int;

    GLFrameBuffer(Size2 size, std::vector<PixelFormat> formats, int samples = 1);
    virtual ~GLFrameBuffer();

    void bind() override;
    void unbind() override;

    std::shared_ptr<Texture2D> getColorAttachment(int index) override;
    std::shared_ptr<Texture2D> getDepthAttachment() override;
    void                       clearColorAttachment(int index, int value) override;

    void read(int index, Vector2i pos, int& data) override;

private:
    void addColorAttachment(PixelFormat format);
    void addDepthAttachment(PixelFormat format);

    handle_type handle;
    Size2       size;
    int         samples;
};

} // namespace clem