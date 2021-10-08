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

void GLCommandBuffer::setViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

} // namespace clem