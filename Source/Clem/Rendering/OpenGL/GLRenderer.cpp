// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLRenderer.h"
#include "Logger.h"
#include <glad/glad.h>

namespace clem
{

GLRenderer& GLRenderer::get()
{
    static auto* instance = new GLRenderer;
    return *instance;
}

void GLRenderer::init()
{
    CLEM_LOG_INFO("render", "Physical Device: {}", glGetString(GL_RENDERER));
}

void GLRenderer::deinit()
{
}

} // namespace clem