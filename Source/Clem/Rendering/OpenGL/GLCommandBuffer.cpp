// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLCommandBuffer.h"
#include <glad/glad.h>

namespace clem
{

void GLCommandBuffer::begin()
{
}

void GLCommandBuffer::end()
{
}

void GLCommandBuffer::setClearColor(const Vector4& color)
{
    glClearColor(color.x, color.y, color.x, color.w);
}

void GLCommandBuffer::setClearDepth(float depth)
{
    glClearDepth(depth);
}

void GLCommandBuffer::clear(uint8_t flags)
{
    GLbitfield glFlags = 0;
    if(flags & CleanFlags::Color)
        glFlags |= GL_COLOR_BUFFER_BIT;
    if(flags & CleanFlags::Depth)
        glFlags |= GL_DEPTH_BUFFER_BIT;
    if(flags & CleanFlags::Stencil)
        glFlags |= GL_STENCIL_BUFFER_BIT;
    glClear(glFlags);
}

void GLCommandBuffer::setViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

} // namespace clem