// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLFrameBuffer.h"
#include "Assert.hpp"
#include "Rendering/Shader.h"
#include "GLRenderer.h"
#include <glad/glad.h>
#include <unordered_map>
#include <unordered_set>

namespace clem
{

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLFormat = {
    {FrameBuffer::PixelFormat::RGBA8, GL_RGBA},
    {FrameBuffer::PixelFormat::RGB8, GL_RGB},
    {FrameBuffer::PixelFormat::R8, GL_RED_INTEGER},
    {FrameBuffer::PixelFormat::Depth24Stencil8, GL_DEPTH_STENCIL},
    {FrameBuffer::PixelFormat::DepthComponent, GL_DEPTH_COMPONENT}};

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLInternalFormat = {
    {FrameBuffer::PixelFormat::RGBA8, GL_RGBA8},
    {FrameBuffer::PixelFormat::RGB8, GL_RGB8},
    {FrameBuffer::PixelFormat::R8, GL_R32I},
    {FrameBuffer::PixelFormat::Depth24Stencil8, GL_DEPTH24_STENCIL8},
    {FrameBuffer::PixelFormat::DepthComponent, GL_DEPTH_COMPONENT}};

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLType = {
    {FrameBuffer::PixelFormat::RGBA8, GL_UNSIGNED_BYTE},
    {FrameBuffer::PixelFormat::RGB8, GL_UNSIGNED_BYTE},
    {FrameBuffer::PixelFormat::R8, GL_UNSIGNED_BYTE},
    {FrameBuffer::PixelFormat::Depth24Stencil8, GL_UNSIGNED_INT_24_8},
    {FrameBuffer::PixelFormat::DepthComponent, GL_FLOAT}};

static std::unordered_set<FrameBuffer::PixelFormat> colorAttachmentFormat =
    {FrameBuffer::PixelFormat::RGBA8, FrameBuffer::PixelFormat::RGB8, FrameBuffer::PixelFormat::R8};

static std::unordered_set<FrameBuffer::PixelFormat> depthAttachmentFormat =
    {FrameBuffer::PixelFormat::Depth24Stencil8, FrameBuffer::PixelFormat::DepthComponent};

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
            Assert::isTrue(false, "unknown pixel format");
    }

    /*
    if(colorAttachments.empty())
        glDrawBuffer(GL_NONE);
    else
    {
        std::vector<GLenum> bufs;
        for(int i = 0; i < colorAttachments.size(); i++)
            bufs.push_back(GL_COLOR_ATTACHMENT0 + i);
        glDrawBuffers(colorAttachments.size(), bufs.data());
    }
    */

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
    auto id = (GLuint)depthAttachments->getHandle();
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
    return depthAttachments;
}

void GLFrameBuffer::clearColorAttachment(int index, int value)
{
    bind();
    glClearTexImage((GLuint)colorAttachments[index]->getHandle(), 0, GL_RED_INTEGER, GL_INT, &value);
    GLCheckError();
    unbind();
}

void GLFrameBuffer::read(int index, Vector2i pos, int& data)
{
    Assert::isTrue(0 <= index && index < colorAttachments.size());

    bind();
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glReadPixels(pos.x, pos.y, 1, 1, GL_RED_INTEGER, GL_INT, &data);
    unbind();
}

void GLFrameBuffer::addColorAttachment(PixelFormat format)
{
    Assert::isTrue(colorAttachmentFormat.contains(format));

    if(samples == 1)
    {
        auto attach = Texture2D::create();
        attach->bind();

        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GLInternalFormat[format], (GLsizei)size.x, (GLsizei)size.y, 0, GLFormat[format], GLType[format], nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)colorAttachments.size(), GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);

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

void GLFrameBuffer::addDepthAttachment(PixelFormat format)
{
    Assert::isTrue(depthAttachmentFormat.contains(format));

    if(samples == 1)
    {
        auto attach = Texture2D::create();
        attach->bind();

        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        if(format == PixelFormat::Depth24Stencil8)
        {
            glTexStorage2D(GL_TEXTURE_2D, 1, GLInternalFormat[format], (GLsizei)size.x, (GLsizei)size.y);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
        }
        else if(format == PixelFormat::DepthComponent)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GLInternalFormat[format], (GLsizei)size.x, (GLsizei)size.y, 0, GLFormat[format], GLType[format], nullptr);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)attach->getHandle(), 0);
        }
        else
            Assert::isTrue(false);

        depthAttachments = attach;
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