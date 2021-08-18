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

    GLFrameBuffer(Size2 size, int samples);
    virtual ~GLFrameBuffer();

    void bind() override;
    void unbind() override;

    handle_type colorAttachment;
    handle_type depthAttachment;

private:
    void attachColor();
    void attachDepth();

    handle_type handle;
    Size2       size;
    int         samples;
};

} // namespace clem