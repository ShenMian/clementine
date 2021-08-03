// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "OpenGL/GLShader.h"
#include "Renderer.h"

namespace clem
{

std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;
    case OpenGL:
        return std::make_shared<GLShader>(vertexSrc, fragmentSrc);
    }
    return nullptr;
}

std::shared_ptr<Shader> Shader::create(const std::filesystem::path& path)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;
    case OpenGL:
        return std::make_shared<GLShader>(path);
    }
    return nullptr;
}

} // namespace clem