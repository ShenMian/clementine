// Copyright 2021 SMS
// License(Apache-2.0)

#include "FrameBuffer.h"

#pragma once

namespace clem
{

class GBuffer
{
public:
    enum TextureType : int
    {
        Position,
        Normals,
        AlbedoSpec
        // PBR,
        // DepthStencil
    };

    GBuffer(const Size2i& size);

    void bind();
    void unbind();

    std::shared_ptr<Texture2D> getTexture(int i);

private:
    std::vector<std::shared_ptr<Texture2D>> textures;
    std::shared_ptr<FrameBuffer>            framebuffer;
};

} // namespace clem
