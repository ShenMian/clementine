// Copyright 2021 SMS
// License(Apache-2.0)

#include "GBuffer.h"

namespace clem
{

GBuffer::GBuffer(const Size2i& size)
{
    textures.push_back(Texture2D::create(size, Texture2D::Format::RGB8));
    textures.push_back(Texture2D::create(size, Texture2D::Format::RGB8));
    textures.push_back(Texture2D::create(size, Texture2D::Format::RGBA8));
    framebuffer = FrameBuffer::create(size, textures);
}

void GBuffer::bind()
{
    framebuffer->bind();
}

void GBuffer::unbind()
{
    framebuffer->unbind();
}

std::shared_ptr<Texture2D> GBuffer::getTexture(int i)
{
    return textures[i];
}

} // namespace clem