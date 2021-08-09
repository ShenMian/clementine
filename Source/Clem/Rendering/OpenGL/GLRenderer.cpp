// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLRenderer.h"
#include "Logging/Logging.h"
#include "Rendering/VertexArray.h"
#include <glad/glad.h>

namespace clem
{

GLRenderer& GLRenderer::get()
{
    static auto* instance = new GLRenderer;
    return *instance;
}

void GLRenderer::submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader)
{
    vertexArray->bind();
    shader->bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
    assert(glGetError() == GL_NO_ERROR);
}

void GLRenderer::init()
{
    CLEM_LOG_INFO("render", std::format("physical device: {}", (const char*)glGetString(GL_RENDERER)));
}

void GLRenderer::deinit()
{
}

} // namespace clem