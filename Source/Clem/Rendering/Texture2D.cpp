// Copyright 2021 SMS
// License(Apache-2.0)

#include "Texture2D.h"
#include "OpenGL/GLTexture2D.h"
#include "Renderer.h"

namespace fs = std::filesystem;

namespace clem
{

std::unordered_map<std::filesystem::path, std::shared_ptr<Texture2D>> Texture2D::cache;

std::shared_ptr<Texture2D> Texture2D::create()
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return GLTexture2D::create();
    }
    return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::create(const fs::path& path, Type type)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        auto texture = GLTexture2D::create(path);
        texture->setType(type);
        return texture;
    }
    return nullptr;
}

void Texture2D::setType(Type type)
{
    this->type = type;
}

Texture2D::Type Texture2D::getType() const
{
    return type;
}

} // namespace clem