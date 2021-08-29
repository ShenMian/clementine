// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLRenderer.h"
#include "Logging/Logging.h"
#include "Rendering/CommandBuffer.h"
#include "Rendering/Material.h"
#include "Rendering/Mesh.h"
#include "Rendering/Model.h"
#include "Rendering/VertexArray.h"
#include <glad/glad.h>

namespace clem
{

const char* GLGetErrorString(GLenum error)
{
    switch(error)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";

    default:
        return "unknown";
    }
}

void GLCheckError()
{
    while(const auto error = glGetError())
    {
        if(error == GL_NO_ERROR)
            break;

        Assert::isTrue(false, std::format("OpenGL unknown error: ({}): {}", error, GLGetErrorString(error)));
    }
}

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR)
        ;
}

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
    if(entity.get<Tag>().str == "skybox")
    {
        auto shader = Shader::get("skybox_sphere");
        auto& mesh = entity.get<Model>().getMeshs()[0];

        shader->bind();

        entity.get<Material>().tex.diffuse->bind(10);
        shader->uploadUniform("u_skybox", 10);

        glDepthFunc(GL_LEQUAL);
        draw(mesh.vertexArray);
        glDepthFunc(GL_LESS);

        return;
    }

    auto shader = Shader::get("standard");

    auto& transform = entity.get<Transform>();
    auto& model     = entity.get<Model>();

    auto& meshs = model.getMeshs();
    auto& mats  = model.getMaterials();

    if(meshs.empty())
        return;

    shader->bind();
    shader->uploadUniform("u_model", transform);
    shader->uploadUniform("u_entity_id", (int)entity.id());

    for(size_t i = 0; i < meshs.size(); i++)
    {
        shader->uploadUniform("u_material.ambient", mats[i].ambient);
        shader->uploadUniform("u_material.diffuse", mats[i].diffuse);
        shader->uploadUniform("u_material.specular", mats[i].specular);
        shader->uploadUniform("u_material.emission", mats[i].emission);
        shader->uploadUniform("u_material.shininess", mats[i].shininess);

        if(mats[i].tex.ambient)
            mats[i].tex.ambient->bind(0);

        if(mats[i].tex.diffuse)
            mats[i].tex.diffuse->bind(1);

        if(mats[i].tex.specular)
            mats[i].tex.specular->bind(2);

        if(mats[i].tex.specular_highlight)
            mats[i].tex.specular_highlight->bind(3);

        if(mats[i].tex.emissive)
            mats[i].tex.emissive->bind(4);

        shader->uploadUniform("u_material.tex.ambient", 0);
        shader->uploadUniform("u_material.tex.diffuse", 1);
        shader->uploadUniform("u_material.tex.specular", 2);
        shader->uploadUniform("u_material.tex.specular_highlight", 3);
        shader->uploadUniform("u_material.tex.emissive", 4);

        draw(meshs[i].vertexArray);
    }

    GLCheckError();
}

void GLRenderer::submit(const Entity& entity, std::shared_ptr<Shader> shader)
{
    Assert::isTrue(false);
}

void GLRenderer::submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader, const Matrix4& transform)
{
    Assert::isTrue(false);
}

void GLRenderer::setViewport(int x, int y, int w, int h)
{
    Assert::isTrue(cmdBuffer != nullptr);
    cmdBuffer->setViewport(x, y, w, h);
}

void GLRenderer::draw(std::shared_ptr<VertexArray> vertexArray)
{
    vertexArray->bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
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