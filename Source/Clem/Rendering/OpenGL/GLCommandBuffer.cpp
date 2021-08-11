// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLCommandBuffer.h"
#include <glad/glad.h>

namespace clem
{

void GLCommandBuffer::beginFrame()
{
    glClearColor(30.f / 255, 144.f / 255, 255.f / 255, 1.f); // ºþÀ¶É«
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLCommandBuffer::endFrame()
{
}

void GLCommandBuffer::setViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

} // namespace clem