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
        return std::make_shared<GLTexture2D>();
    }
    return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::create(const Size2i size, Format fmt)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLTexture2D>(size, fmt);
    }
    return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::create(const fs::path& path, bool genMipmap, Format fmt)
{
    auto it = cache.find(path);
    if(it != cache.end())
        return it->second;

    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        auto tex = std::make_shared<GLTexture2D>(path, genMipmap, fmt);
        cache.insert({path, tex});
        return tex;
    }
    return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::create(const void* data, Size2i size, int bits, bool genMipmap, Format fmt)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLTexture2D>(data, size, bits, genMipmap, fmt);
    }
    return nullptr;
}

Size2i Texture2D::getSize() const
{
    return size;
}

Texture2D::Format Texture2D::getFormat() const
{
    return format;
}

} // namespace clem