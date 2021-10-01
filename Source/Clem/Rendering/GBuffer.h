// Copyright 2021 SMS
// License(Apache-2.0)

#include "FrameBuffer.h"

#pragma once

namespace clem
{

class GBuffer
{
public:
    enum class TextureType
    {
        Position,
        Normals,
        AlbedoSpec,
        // PBR,
        DepthStencil
    };

    GBuffer(const Size2i& size);

    void bind();
    void unbind();

    std::shared_ptr<Texture2D> getTexture(TextureType type);

private:
    std::unordered_map<TextureType, std::shared_ptr<Texture2D>> textures;
    std::shared_ptr<FrameBuffer>                                framebuffer;
};

} // namespace clem
