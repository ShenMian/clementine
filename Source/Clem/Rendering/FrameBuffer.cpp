// Copyright 2021 SMS
// License(Apache-2.0)

#include "FrameBuffer.h"
#include "OpenGL/GLFrameBuffer.h"
#include "Renderer.h"

namespace clem
{

std::shared_ptr<FrameBuffer> clem::FrameBuffer::create(Size2 size, std::vector<PixelFormat> attachs, int samples)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLFrameBuffer>(size, attachs, samples);
    }
    return nullptr;
}

} // namespace clem