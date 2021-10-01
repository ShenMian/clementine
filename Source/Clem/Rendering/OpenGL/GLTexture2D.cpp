// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLTexture2D.h"
#include "Core/Assert.hpp"
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

static std::unordered_map<int, Texture2D::Format> BitsToFormat = {
    {8, Texture2D::Format::R8},
    {16, Texture2D::Format::RG8},
    {24, Texture2D::Format::RGB8},
    {32, Texture2D::Format::RGBA8},
    {48, Texture2D::Format::RGB16},
    {64, Texture2D::Format::RGBA16}};

static_assert(std::is_same<GLTexture2D::handle_type, GLuint>::value);

GLTexture2D::GLTexture2D()
{
    glType = GL_TEXTURE_2D;
    glCreateTextures(glType, 1, &handle);
}

GLTexture2D::GLTexture2D(const Size2i& size, Format fmt)
{
    Assert::isTrue(fmt != Format::Auto);

    this->size   = size;
    this->format = fmt;

    glType = GL_TEXTURE_2D;
    glCreateTextures(glType, 1, &handle);
    glTextureStorage2D(handle, 1, GLInternalFormat(fmt), size.x, size.y);
}

GLTexture2D::GLTexture2D(const fs::path& path, bool genMipmap, Format fmt)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    this->format = fmt;
    this->path   = path;

    int  bits;
    auto data = loadFromFile(path, size.x, size.y, bits);
    init(data, size, bits, genMipmap, fmt);
    stbi_image_free(data);
}

GLTexture2D::GLTexture2D(const void* data, Size2i size, int bits, bool genMipmap, Format fmt)
{
    this->size   = size;
    this->format = fmt;

    init(data, size, bits, genMipmap, fmt);
}

GLTexture2D::~GLTexture2D()
{
    glDeleteTextures(1, &handle);
}

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

void GLTexture2D::setSWarp(Warp warp)
{
    bind();
    glTexParameteri(glType, GL_TEXTURE_WRAP_S, GLWarp[warp]);
    GLCheckError();
}

void GLTexture2D::setTWarp(Warp warp)
{
    bind();
    glTexParameteri(glType, GL_TEXTURE_WRAP_T, GLWarp[warp]);
    GLCheckError();
}

void GLTexture2D::bind(unsigned int slot) const
{
    glBindTextureUnit(slot, handle);
    GLCheckError();
}

size_t GLTexture2D::getHandle() const
{
    return (size_t)handle;
}

void GLTexture2D::init(const void* data, Size2i size, int bits, bool genMipmap, Format fmt)
{
    glType = GL_TEXTURE_2D;
    glCreateTextures(glType, 1, &handle);
    bind();

    setMinFilter(Filter::Nearest);
    setMagFilter(Filter::Bilinear);
    setSWarp(Warp::Repeat);
    setTWarp(Warp::Repeat);

    if(fmt == Format::Auto)
        fmt = BitsToFormat[bits];

    glTexImage2D(glType, 0, GLInternalFormat(fmt), size.x, size.y, 0, GLFormat(fmt), GL_UNSIGNED_BYTE, data);

    if(genMipmap)
        glGenerateMipmap(glType);

    GLCheckError();
}

void* GLTexture2D::loadFromFile(const std::filesystem::path& path, int& width, int& height, int& bits)
{
    // stbi_set_flip_vertically_on_load(1);
    int  channels;
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    Assert::isTrue(data != nullptr, std::format("can't load image from file: '{}'", path.string()));
    bits = channels * 8;
    return data;
}

uint32_t GLTexture2D::GLInternalFormat(Format fmt)
{
    switch(fmt)
    {
    case Format::RGBA8:
        return GL_RGBA8;

    case Format::RGB8:
        return GL_RGB8;

    case Format::RG8:
        return GL_RG8;

    case Format::R8:
        return GL_R8;

    case Format::DepthStencil:
        return GL_DEPTH24_STENCIL8;

    default:
        Assert::isTrue(false, "no corresponding GL internal format");
        return 0;
    }
}

uint32_t GLTexture2D::GLFormat(Format fmt)
{
    switch(fmt)
    {
    case Format::RGBA8:
        return GL_RGBA;

    case Format::RGB8:
        return GL_RGB;

    case Format::RG8:
        return GL_RG;

    case Format::R8:
        return GL_RED;

    default:
        Assert::isTrue(false, "no corresponding GL format");
        return 0;
    }
}

} // namespace clem