// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "Renderer.h"

#include "OpenGL/GLShader.h"
#include "Vulkan/VKShader.h"

namespace clem
{

std::shared_ptr<Shader_> Shader_::create(const std::string& name, Stage stage)
{
    switch(Renderer_::getAPI())
    {
        using enum Renderer_::API;

    case OpenGL:
        return std::make_shared<GLShader_>(name, stage);

    case Vulkan:
        return std::make_shared<VKShader_>(name, stage);
    }
    return nullptr;
}


Shader_::Shader_(const std::string& name, Stage stage)
    : name(name), stage(stage)
{
}

void Shader_::setName(const std::string& name)
{
    this->name = name;
}

const std::string& Shader_::getName() const
{
    return name;
}

} // namespace clem