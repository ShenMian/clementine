// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "OpenGL/GLShader.h"
#include "Renderer.h"
#include "Vulkan/VKShader.h"

namespace clem
{

std::unordered_map<std::string, std::shared_ptr<Shader>> Shader::cache;

std::shared_ptr<Shader> Shader::load(const std::string& name)
{
    const auto it = cache.find(name);
    if(it == cache.end())
    {
        std::shared_ptr<Shader> result;
        switch(Renderer::getAPI())
        {
            using enum Renderer::API;

        case OpenGL:
            result = std::make_shared<GLShader>(name);
            break;

        case Vulkan:
            result = std::make_shared<VKShader>(name);
            break;
        }
        cache.insert({name, result});
        return result;
    }
    else
        return it->second;
}

std::shared_ptr<Shader> Shader::create(const std::filesystem::path& vertShader, const std::filesystem::path& fragShader)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLShader>(vertShader, fragShader);

    case Vulkan:
        return std::make_shared<VKShader>(vertShader, fragShader);
    }
    return nullptr;
}

Shader::Shader(const std::string& name)
    : name(name)
{
}

const std::string& Shader::getName() const
{
    return name;
}

void Shader::unload(const std::string& name)
{
    cache.erase(name);
}

std::shared_ptr<Shader> Shader::reload(const std::string& name)
{
    const auto shader = load(name);
    cache[name]       = shader;
    return shader;
}

std::shared_ptr<Shader> Shader::get(const std::string& name)
{
    Assert::isTrue(cache.contains(name));
    return cache[name];
}

} // namespace clem