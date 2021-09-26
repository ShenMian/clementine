// Copyright 2021 SMS
// License(Apache-2.0)

#include "FrameBuffer.h"
#include "OpenGL/GLFrameBuffer.h"
#include "Renderer.h"

namespace clem
{

std::shared_ptr<FrameBuffer> FrameBuffer::create(Size2i size, const std::vector<std::shared_ptr<Texture2D>>& attachs, int samples)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLFrameBuffer>(size, attachs, samples);
    }
    return nullptr;
}

std::shared_ptr<FrameBuffer> FrameBuffer::create(Size2i size, const std::vector<PixelFormat>& formats, int samples)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLFrameBuffer>(size, formats, samples);
    }
    return nullptr;
}

} // namespace clem