// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "OpenGL/GLShader.h"
#include "Renderer.h"
#include "Vulkan/VKShader.h"

namespace clem
{

std::shared_ptr<Shader> Shader::create(const std::string& name)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLShader>(name);
    }
    return nullptr;
}

std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLShader>(vertexSrc, fragmentSrc);

    case Vulkan:
        return std::make_shared<VKShader>(vertexSrc, fragmentSrc);
    }
    return nullptr;
}

} // namespace clem