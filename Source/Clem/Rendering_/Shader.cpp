// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "Renderer.h"
#include <cassert>

#include "OpenGL/GLShader.h"
#include "Vulkan/VKShader.h"

namespace clem
{

std::unordered_map<Shader_::Stage, const char*> Shader_::extension = {
    {Shader_::Stage::Vertex, "vert"},
    {Shader_::Stage::Geometry, "geom"},
    {Shader_::Stage::Fragment, "frag"},
    {Shader_::Stage::Compute, "comp"}};

std::shared_ptr<Shader_> Shader_::create(const std::string& name, Stage stage)
{
    switch(Renderer_::getAPI())
    {
        using enum Renderer_::API;

    case OpenGL:
        return std::make_shared<GLShader_>(name, stage);

    case Vulkan:
        return std::make_shared<VKShader_>(name, stage);

    default:
        assert(false);
    }
    return nullptr;
}

Shader_::Shader_(const std::string& name, Stage stage)
    : name(name), stage(stage)
{
}

const std::string& Shader_::getName() const
{
    return name;
}

Shader_::Stage Shader_::getStage() const
{
    return stage;
}

} // namespace clem