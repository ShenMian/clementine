// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLFrameBuffer.h"
#include "Assert.hpp"
#include "Rendering/Shader.h"
#include <glad/glad.h>
#include <unordered_map>

namespace clem
{

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLFormat = {
    {FrameBuffer::PixelFormat::I8, GL_RED_INTEGER},
    {FrameBuffer::PixelFormat::RGBA8, GL_RGBA}};

static std::unordered_map<FrameBuffer::PixelFormat, GLenum> GLInternalFormat = {
    {FrameBuffer::PixelFormat::I8, GL_R32I},
    {FrameBuffer::PixelFormat::RGBA8, GL_RGBA8}};

GLFrameBuffer::GLFrameBuffer(Size2 size, std::vector<PixelFormat> attachs, int samples)
    : size(size), samples(samples)
{
    glCreateFramebuffers(1, &handle);
    bind();

    for(auto format : attachs)
        addColorAttachment(format);
    addDepthAttachment();

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
}

void GLFrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
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
    glClearTexImage(colorAttachments[index]->getHandle(), 0, GL_RED_INTEGER, GL_INT, &value);
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
    if(format == PixelFormat::Auto)
        format = PixelFormat::RGBA8;

    if(samples > 1)
    {
        /*
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorAttachment);

        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, (GLsizei)size.x, (GLsizei)size.y, GL_FALSE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorAttachment, 0);
        */
    }
    else
    {
        auto attach = Texture2D::create();
        attach->bind();

        glTexImage2D(GL_TEXTURE_2D, 0, GLInternalFormat[format], (GLsizei)size.x, (GLsizei)size.y, 0, GLFormat[format], GL_UNSIGNED_BYTE, nullptr);

        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachments.size(), GL_TEXTURE_2D, attach->getHandle(), 0);

        colorAttachments.push_back(attach);
    }
    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

void GLFrameBuffer::addDepthAttachment()
{
    if(samples > 1)
    {
        /*
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &depthAttachment);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depthAttachment);
        glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH24_STENCIL8, (GLsizei)size.x, (GLsizei)size.y, false);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, depthAttachment, 0);
        */
    }
    else
    {
        auto attach = Texture2D::create();
        attach->bind();

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, (GLsizei)size.x, (GLsizei)size.y);

        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, attach->getHandle(), 0);

        depthAttachments = attach;
    }
    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

} // namespace clem