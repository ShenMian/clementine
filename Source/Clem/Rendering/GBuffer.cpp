// Copyright 2021 SMS
// License(Apache-2.0)

#include "GBuffer.h"

namespace clem
{

GBuffer::GBuffer(const Size2i& size)
{
    for(int i = 0; i < TextureType::Num; i++)
        textures.push_back(Texture2D::create(size));
    framebuffer = FrameBuffer::create(size, textures);
}

} // namespace clem