// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLTexture2D.h"
#include "Assert.hpp"
#include <cassert>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <type_traits>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace fs = std::filesystem;

namespace clem
{

static_assert(std::is_same<GLTexture2D::id_type, GLuint>::value);

GLTexture2D::GLTexture2D(const fs::path& path)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    int  channels;
    auto data = loadFromFile(path, size.x, size.y, channels);

    GLenum internalFormat, dataFormat;
    switch(channels)
    {
    case 3:
        internalFormat = GL_RGB8;
        dataFormat     = GL_RGB;
        break;

    case 4:
        internalFormat = GL_RGBA8;
        dataFormat     = GL_RGBA;
        break;

    default:
        assert(false && "format not supported");
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &handle_);
    glTextureStorage2D(handle_, 1, internalFormat, size.x, size.y);

    // 设置纹理环绕方式
    glTextureParameteri(handle_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(handle_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 设置纹理过滤
    glTextureParameteri(handle_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(handle_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTextureParameteri(handle_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTextureParameteri(handle_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureSubImage2D(handle_, 0, 0, 0, size.x, size.y, dataFormat, GL_UNSIGNED_BYTE, data);

    assert(glGetError() == GL_NO_ERROR);

    stbi_image_free(data);
}

GLTexture2D::~GLTexture2D()
{
    glDeleteTextures(1, &handle_);
}

void GLTexture2D::bind(id_type slot)
{
    glBindTextureUnit(slot, handle_);
}

Size2i GLTexture2D::getSize() const
{
    return size;
}

void* GLTexture2D::getHandle()
{
    return &handle_;
}

void* GLTexture2D::loadFromFile(const std::filesystem::path& path, int& width, int& height, int& channels)
{
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    assert(data);

    return data;
}

} // namespace clem