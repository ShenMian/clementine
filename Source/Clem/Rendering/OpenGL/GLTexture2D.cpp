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

static std::unordered_map<Texture2D::Filter, GLenum> GLFilter = {
    {Texture2D::Filter::Nearest, GL_NEAREST},
    {Texture2D::Filter::Linear, GL_LINEAR}};

static std::unordered_map<Texture2D::Warp, GLenum> GLWarp = {
    {Texture2D::Warp::Repeat, GL_REPEAT},
    {Texture2D::Warp::MirrorRepeat, GL_MIRRORED_REPEAT},
    {Texture2D::Warp::ClampToDege, GL_CLAMP_TO_EDGE}};

static_assert(std::is_same<GLTexture2D::handle_type, GLuint>::value);

GLTexture2D::GLTexture2D(const fs::path& path)
{
    load(path);
}

GLTexture2D::~GLTexture2D()
{
    glDeleteTextures(1, &handle_);
}

void GLTexture2D::load(const std::filesystem::path& path)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    type = GL_TEXTURE_2D;

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
        Assert::isTrue(false, "format not supported");
    }

    glCreateTextures(type, 1, &handle_);
    // glActiveTexture(GL_TEXTURE0); // 激活纹理单元
    glBindTexture(type, handle_);

    glTexStorage2D(type, 1, internalFormat, size.x, size.y);

    // 设置纹理过滤方式
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 设置纹理环绕方式
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexSubImage2D(type, 0, 0, 0, size.x, size.y, dataFormat, GL_UNSIGNED_BYTE, data);

    assert(glGetError() == GL_NO_ERROR);

    stbi_image_free(data);
}

// TODO: Texture3D?
void GLTexture2D::loadCubemap(const std::vector<std::filesystem::path>& faces)
{
    Assert::isTrue(faces.size() == 6, "skybox should have 6 faces");

    type = GL_TEXTURE_CUBE_MAP;

    glCreateTextures(type, 1, &handle_);
    glBindTexture(type, handle_);

    // 读取六个面
    for(GLuint i = 0; i < faces.size(); i++)
    {
        int  channels;
        auto data = loadFromFile(faces[i], size.x, size.y, channels);

        GLenum dataFormat;
        if(channels == 3)
            dataFormat = GL_RGB;
        else if(channels == 4)
            dataFormat = GL_RGBA;
        else
            Assert::isTrue(false, "format not supported");

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGB, size.x, size.y, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    // 设置纹理过滤方式
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 设置纹理环绕方式
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(type, 0);
}

void GLTexture2D::bind(unsigned int slot)
{
    glBindTextureUnit(slot, handle_);

    glBindTexture(type, handle_);
}

Size2i GLTexture2D::getSize() const
{
    return size;
}

size_t GLTexture2D::getHandle()
{
    return (size_t)handle_;
}

void* GLTexture2D::loadFromFile(const std::filesystem::path& path, int& width, int& height, int& channels)
{
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    Assert::isTrue(data != nullptr, std::format("can't load from file: '{}'", path.string()));

    return data;
}

} // namespace clem