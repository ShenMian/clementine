// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLFrameBuffer.h"
#include "Core/Assert.hpp"
#include "GLRenderer.h"
#include "Rendering/Shader.h"
#include <glad/glad.h>
#include <unordered_map>
#include <unordered_set>

namespace clem
{

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLFormat = {
    {FrameBuffer::PixelFormat::RGBA8, GL_RGBA},
    {FrameBuffer::PixelFormat::RGB8, GL_RGB},
    {FrameBuffer::PixelFormat::R8, GL_RED_INTEGER},
    {FrameBuffer::PixelFormat::DepthStencil, GL_DEPTH_STENCIL},
    {FrameBuffer::PixelFormat::Depth, GL_DEPTH_COMPONENT}};

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLInternalFormat = {
    {FrameBuffer::PixelFormat::RGBA8, GL_RGBA8},
    {FrameBuffer::PixelFormat::RGB8, GL_RGB8},
    {FrameBuffer::PixelFormat::R8, GL_R32I},
    {FrameBuffer::PixelFormat::DepthStencil, GL_DEPTH24_STENCIL8},
    {FrameBuffer::PixelFormat::Depth, GL_DEPTH_COMPONENT}};

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLType = {
    {FrameBuffer::PixelFormat::RGBA8, GL_UNSIGNED_BYTE},
    {FrameBuffer::PixelFormat::RGB8, GL_UNSIGNED_BYTE},
    {FrameBuffer::PixelFormat::R8, GL_UNSIGNED_BYTE},
    {FrameBuffer::PixelFormat::DepthStencil, GL_UNSIGNED_INT_24_8},
    {FrameBuffer::PixelFormat::Depth, GL_FLOAT}};

static std::unordered_set<FrameBuffer::PixelFormat> colorAttachmentFormat =
    {FrameBuffer::PixelFormat::RGBA8, FrameBuffer::PixelFormat::RGB8, FrameBuffer::PixelFormat::R8};

static std::unordered_set<FrameBuffer::PixelFormat> depthAttachmentFormat =
    {FrameBuffer::PixelFormat::DepthStencil, FrameBuffer::PixelFormat::Depth, FrameBuffer::PixelFormat::Stencil};

GLFrameBuffer::GLFrameBuffer(Size2i size, const std::vector<std::shared_ptr<Texture2D>>& attachs, int samples)
    : samples(samples)
{
    Assert::isTrue(attachs.size() > 0);
    Assert::isTrue(samples > 0);

    this->size = size;

    glCreateFramebuffers(1, &handle);
    bind();

    for(const auto& attach : attachs)
    {
        if(colorAttachmentFormat.contains(attach->getFormat()))
            addColorAttachment(attach);
        else if(depthAttachmentFormat.contains(attach->getFormat()))
            addDepthAttachment(attach);
        else
            Assert::isTrue(false, "unknown format");
    }

#if 0
    if(colorAttachments.empty())
        glDrawBuffer(GL_NONE);
    else
    {
        std::vector<GLenum> bufs;
        for(int i = 0; i < colorAttachments.size(); i++)
            bufs.push_back(GL_COLOR_ATTACHMENT0 + i);
        glDrawBuffers((GLsizei)colorAttachments.size(), bufs.data());
    }
#endif

    Assert::isTrue(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    unbind();
}

GLFrameBuffer::GLFrameBuffer(Size2i size, const std::vector<PixelFormat>& formats, int samples)
    : samples(samples)
{
    Assert::isTrue(formats.size() > 0);
    Assert::isTrue(samples > 0);

    this->size = size;

    glCreateFramebuffers(1, &handle);
    bind();

    for(const auto& format : formats)
    {
        if(colorAttachmentFormat.contains(format))
            addColorAttachment(format);
        else if(depthAttachmentFormat.contains(format))
            addDepthAttachment(format);
        else
            Assert::isTrue(false, "unknown format");
    }

#if 0
    if(colorAttachments.empty())
        glDrawBuffer(GL_NONE);
    else
    {
        std::vector<GLenum> bufs;
        for(int i = 0; i < colorAttachments.size(); i++)
            bufs.push_back(GL_COLOR_ATTACHMENT0 + i);
        glDrawBuffers((GLsizei)colorAttachments.size(), bufs.data());
    }
#endif

    Assert::isTrue(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    unbind();
}

GLFrameBuffer::~GLFrameBuffer()
{
    glDeleteFramebuffers(1, &handle);

    for(auto& attach : colorAttachments)
    {
        auto id = (GLuint)attach->getHandle();
        glDeleteTextures(1, &id);
    }
    auto id = (GLuint)depthAttachment->getHandle();
    glDeleteTextures(1, &id);
}

static GLint defaultFBO = 0;

void GLFrameBuffer::bind()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, handle);

    GLCheckError();
}

void GLFrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    GLCheckError();
}

std::shared_ptr<Texture2D> GLFrameBuffer::getColorAttachment(int index)
{
    Assert::isTrue(0 <= index && index < colorAttachments.size());
    return colorAttachments[index];
}

std::shared_ptr<Texture2D> GLFrameBuffer::getDepthAttachment()
{
    return depthAttachment;
}

void GLFrameBuffer::clearColorAttachment(int index, int value)
{
    bind();
    glClearTexImage((GLuint)colorAttachments[index]->getHandle(), 0, GL_RED_INTEGER, GL_INT, &value);
    GLCheckError();
    unbind();
}

void GLFrameBuffer::readColorAttachment(int index, Vector2i pos, int& data)
{
    Assert::isTrue(0 <= index && index < colorAttachments.size());

    bind();
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glReadPixels(pos.x, pos.y, 1, 1, GL_RED_INTEGER, GL_INT, &data);
    unbind();
}

void GLFrameBuffer::addColorAttachment(std::shared_ptr<Texture2D> attach)
{
    Assert::isTrue(colorAttachmentFormat.contains(attach->getFormat()));

    attach->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)colorAttachments.size(), GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
    colorAttachments.push_back(attach);

    GLCheckError();
}

void GLFrameBuffer::addDepthAttachment(std::shared_ptr<Texture2D> attach)
{
    Assert::isTrue(depthAttachmentFormat.contains(attach->getFormat()));

    attach->bind();
    if(attach->getFormat() == PixelFormat::DepthStencil)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
    else if(attach->getFormat() == PixelFormat::Depth)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
    else if(attach->getFormat() == PixelFormat::Stencil)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
    // glDrawBuffers(0, GL_NONE);

    depthAttachment = attach;

    GLCheckError();
}

void GLFrameBuffer::addColorAttachment(PixelFormat fmt)
{
    Assert::isTrue(colorAttachmentFormat.contains(fmt));

    if(samples == 1)
    {
        auto attach = Texture2D::create();
        attach->bind();

        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);
        attach->setSWarp(Texture2D::Warp::ClampToEdge);
        attach->setTWarp(Texture2D::Warp::ClampToEdge);

        glTexImage2D(GL_TEXTURE_2D, 0, GLInternalFormat[fmt], (GLsizei)size.x, (GLsizei)size.y, 0, GLFormat[fmt], GLType[fmt], nullptr);

#if 1
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)colorAttachments.size(), GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
#else
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)colorAttachments.size(), GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
#endif

        colorAttachments.push_back(attach);
    }
    else
    {
        /*
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorAttachment);

        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, (GLsizei)size.x, (GLsizei)size.y, GL_FALSE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)colorAttachments.size(), GL_TEXTURE_2D_MULTISAMPLE, colorAttachment, 0);
        */
    }

    GLCheckError();
}

void GLFrameBuffer::addDepthAttachment(PixelFormat fmt)
{
    Assert::isTrue(depthAttachmentFormat.contains(fmt));

    if(samples == 1)
    {
        auto attach = Texture2D::create();
        attach->bind();

        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);
        attach->setSWarp(Texture2D::Warp::ClampToEdge);
        attach->setTWarp(Texture2D::Warp::ClampToEdge);

        if(fmt == PixelFormat::DepthStencil)
        {
            glTexStorage2D(GL_TEXTURE_2D, 1, GLInternalFormat[fmt], (GLsizei)size.x, (GLsizei)size.y);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
        }
        else if(fmt == PixelFormat::Depth)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GLInternalFormat[fmt], (GLsizei)size.x, (GLsizei)size.y, 0, GLFormat[fmt], GLType[fmt], nullptr);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
        }
        else
            Assert::isTrue(false);

        // glDrawBuffers(0, GL_NONE);

        depthAttachment = attach;
    }
    else
    {
        /*
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &depthAttachment);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depthAttachment);
        glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH24_STENCIL8, (GLsizei)size.x, (GLsizei)size.y, false);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, depthAttachment, 0);
        */
    }
    GLCheckError();
}

} // namespace clem