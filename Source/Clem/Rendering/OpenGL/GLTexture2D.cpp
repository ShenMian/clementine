// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLTexture2D.h"
#include "Assert.hpp"
#include "GLRenderer.h"
#include <cassert>
#include <stb/stb_image.h>
#include <type_traits>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace fs = std::filesystem;

namespace clem
{

static std::unordered_map<Texture2D::Filter, GLenum> GLFilter = {
    {Texture2D::Filter::Nearest, GL_NEAREST},
    {Texture2D::Filter::Bilinear, GL_LINEAR},
    {Texture2D::Filter::Trilinear, GL_LINEAR_MIPMAP_LINEAR}};

static std::unordered_map<Texture2D::Warp, GLenum> GLWarp = {
    {Texture2D::Warp::Repeat, GL_REPEAT},
    {Texture2D::Warp::MirrorRepeat, GL_MIRRORED_REPEAT},
    {Texture2D::Warp::ClampToEdge, GL_CLAMP_TO_EDGE}};

static_assert(std::is_same<GLTexture2D::handle_type, GLuint>::value);

std::shared_ptr<Texture2D> GLTexture2D::create()
{
    return std::make_shared<GLTexture2D>();
}

std::shared_ptr<Texture2D> GLTexture2D::create(const fs::path& path, Format format)
{
    auto it = cache.find(fs::absolute(path));
    if(it == cache.end())
    {
        auto texture = create();
        texture->load(path, format);
        cache.insert({path, texture});
        return texture;
    }
    else
        return it->second;
}

GLTexture2D::GLTexture2D()
{
    glType = GL_TEXTURE_2D;

    glCreateTextures(glType, 1, &handle);
}

GLTexture2D::GLTexture2D(const fs::path& path)
{
    load(path);
}

GLTexture2D::~GLTexture2D()
{
    glDeleteTextures(1, &handle);
}

void GLTexture2D::load(const std::filesystem::path& path, Format format)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    glType = GL_TEXTURE_2D;

    glCreateTextures(glType, 1, &handle);
    bind();

    setMinFilter(Filter::Nearest);
    setMagFilter(Filter::Bilinear);

    // 设置纹理环绕方式
    glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int  bits;
    auto data = loadFromFile(path, size.x, size.y, bits);

    GLenum internalFormat, dataFormat;

    switch(format)
    {
    case Format::Auto:
        switch(bits)
        {
        case 8:
            internalFormat = GL_R8;
            dataFormat     = GL_RED;
            break;

        case 16:
            internalFormat = GL_RG8;
            dataFormat     = GL_RG;
            break;

        case 24:
            internalFormat = GL_RGB8;
            dataFormat     = GL_RGB;
            break;

        case 32:
            internalFormat = GL_RGBA8;
            dataFormat     = GL_RGBA;
            break;

        case 48:
            internalFormat = GL_RGB16;
            dataFormat     = GL_RGB;
            break;

        case 64:
            internalFormat = GL_RGBA16;
            dataFormat     = GL_RGBA;
            break;

        default:
            Assert::isTrue(false);
        }
        break;

    case Format::RGB8:
        internalFormat = GL_RGB8;
        dataFormat     = GL_RGB;
        break;

    case Format::RGBA8:
        internalFormat = GL_RGBA8;
        dataFormat     = GL_RGBA;
        break;

    case Format::R8:
        internalFormat = GL_R8;
        dataFormat     = GL_RED;
        break;

    default:
        Assert::isTrue(false);
    }

    // glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    /*glTexStorage2D(glType, 1, internalFormat, size.x, size.y);
    glTexSubImage2D(glType, 0, 0, 0, size.x, size.y, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);*/

    GLCheckError();

    stbi_image_free(data);
}

// TODO: 应该属于 Texture3D
void GLTexture2D::loadCubemap(const std::vector<std::filesystem::path>& faces)
{
    Assert::isTrue(faces.size() == 6, "skybox should have 6 faces");

    glType = GL_TEXTURE_CUBE_MAP;

    glCreateTextures(glType, 1, &handle);
    bind();

    setMinFilter(Filter::Nearest);
    setMagFilter(Filter::Bilinear);

    // 设置纹理环绕方式
    glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(glType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // 读取六个面
    for(GLuint i = 0; i < faces.size(); i++)
    {
        int  channels;
        auto data = loadFromFile(faces[i], size.x, size.y, channels);

        GLenum format;
        if(channels == 3)
            format = GL_RGB;
        else if(channels == 4)
            format = GL_RGBA;
        else
            Assert::isTrue(false, "format not supported");

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGB, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    glBindTexture(glType, 0);

    GLCheckError();
}

void GLTexture2D::setMinFilter(Filter filter)
{
    Assert::isTrue(filter == Filter::Nearest || filter == Filter::Bilinear || filter == Filter::Trilinear);

    bind();
    glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GLFilter[filter]);
    GLCheckError();
}

void GLTexture2D::setMagFilter(Filter filter)
{
    Assert::isTrue(filter == Filter::Nearest || filter == Filter::Bilinear);

    bind();
    glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, GLFilter[filter]);
    GLCheckError();
}

void GLTexture2D::bind()
{
    glBindTexture(glType, handle);
    GLCheckError();
}

void GLTexture2D::bindUnit(unsigned int slot)
{
    glBindTextureUnit(slot, handle);
    GLCheckError();
}

Size2i GLTexture2D::getSize() const
{
    return size;
}

size_t GLTexture2D::getHandle()
{
    return (size_t)handle;
}

void* GLTexture2D::loadFromFile(const std::filesystem::path& path, int& width, int& height, int& bits)
{
    int  channels;
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    Assert::isTrue(data != nullptr, std::format("can't load image from file: '{}'", path.string()));

    bits = channels * 8;

    return data;
}

} // namespace clem