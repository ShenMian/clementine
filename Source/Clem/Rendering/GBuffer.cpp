// Copyright 2021 SMS
// License(Apache-2.0)

#include "GBuffer.h"

namespace clem
{

GBuffer::GBuffer(const Size2i& size)
{
    std::vector<std::shared_ptr<Texture2D>> array;

    array.push_back(Texture2D::create(size, Texture2D::Format::RGB8));
    textures.emplace(TextureType::Position, array.back());

    array.push_back(Texture2D::create(size, Texture2D::Format::RGB8));
    textures.emplace(TextureType::Normals, array.back());

    array.push_back(Texture2D::create(size, Texture2D::Format::RGBA8));
    textures.emplace(TextureType::AlbedoSpec, array.back());

    array.push_back(Texture2D::create(size, Texture2D::Format::DepthStencil));
    textures.emplace(TextureType::DepthStencil, array.back());

    framebuffer = FrameBuffer::create(size, array);
}

void GBuffer::bind()
{
    framebuffer->bind();
}

void GBuffer::unbind()
{
    framebuffer->unbind();
}

std::shared_ptr<Texture2D> GBuffer::getTexture(TextureType type)
{
    return textures[type];
}

} // namespace clem