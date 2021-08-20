// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLRenderer.h"
#include "Logging/Logging.h"
#include "Rendering/CommandBuffer.h"
#include "Rendering/Material.h"
#include "Rendering/VertexArray.h"
#include <glad/glad.h>

namespace clem
{

GLRenderer& GLRenderer::get()
{
    static auto* instance = new GLRenderer;
    return *instance;
}

void GLRenderer::beginFrame()
{
    cmdBuffer->beginFrame();
}

void GLRenderer::endFrame()
{
    cmdBuffer->endFrame();
}

void GLRenderer::submit(const Entity& entity)
{
    auto& model     = entity.get<Model>();
    auto& transform = entity.get<Transform>();
    auto& material  = entity.get<Material>();

    auto shader = material.shader;

    if(model.vertexArray == nullptr)
        return;

    model.vertexArray->bind();
    shader->bind();

    shader->uploadUniform("u_model", transform.getModelMatrix());

    shader->uploadUniform("u_material.ambient", material.ambient);
    shader->uploadUniform("u_material.diffuse", material.diffuse);
    shader->uploadUniform("u_material.specular", material.specular);
    shader->uploadUniform("u_material.shininess", material.shininess);

    shader->uploadUniform("u_entity_id", (int)entity.id());

    glDrawElements(GL_TRIANGLES, (GLsizei)model.vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
    assert(glGetError() == GL_NO_ERROR);
}

void GLRenderer::submit(const Entity& entity, std::shared_ptr<Shader> shader)
{
    auto& model     = entity.get<Model>();
    auto& transform = entity.get<Transform>();

    if(model.vertexArray == nullptr)
        return;

    model.vertexArray->bind();

    // shader = material.shader;
    shader->bind();

    shader->uploadUniform("u_model", transform.getModelMatrix());

    const auto& material = entity.get<Material>();
    shader->uploadUniform("u_material.ambient", material.ambient);
    shader->uploadUniform("u_material.diffuse", material.diffuse);
    shader->uploadUniform("u_material.specular", material.specular);
    shader->uploadUniform("u_material.shininess", material.shininess);

    glDrawElements(GL_TRIANGLES, (GLsizei)model.vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
    assert(glGetError() == GL_NO_ERROR);
}

void GLRenderer::submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader, const Matrix4& transform)
{
    static_assert(sizeof(IndexBuffer::value_type) == sizeof(unsigned int));

    vertexArray->bind();
    shader->bind();
    shader->uploadUniform("u_model", transform);
    glDrawElements(GL_TRIANGLES, (GLsizei)vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
    assert(glGetError() == GL_NO_ERROR);
}

void GLRenderer::setViewport(int x, int y, int w, int h)
{
    Assert::isTrue(cmdBuffer != nullptr);
    cmdBuffer->setViewport(x, y, w, h);
}

void GLRenderer::init()
{
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    cmdBuffer = CommandBuffer::create();

    CLEM_LOG_INFO("render", std::format("physical device: {}", (const char*)glGetString(GL_RENDERER)));
}

void GLRenderer::deinit()
{
}

} // namespace clem