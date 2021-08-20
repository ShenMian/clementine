// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLFrameBuffer.h"
#include "Assert.hpp"
#include <glad/glad.h>

namespace clem
{

GLFrameBuffer::GLFrameBuffer(Size2 size, int samples)
    : size(size), samples(samples)
{
    glCreateFramebuffers(1, &handle);
    bind();

    addColorAttachment();
    addColorAttachment();
    addDepthAttachment();
    Assert::isTrue(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    unbind();
}

GLFrameBuffer::~GLFrameBuffer()
{
    glDeleteFramebuffers(1, &handle);

    for(auto& attach : colorAttachment)
    {
        GLuint id = attach->getHandle();
        glDeleteTextures(1, &id);
    }
    GLuint id = depthAttachment->getHandle();
    glDeleteTextures(1, &id);
}

static GLint defaultFBO;

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
    Assert::isTrue(0 <= index && index < colorAttachment.size());
    return colorAttachment[index];
}

std::shared_ptr<Texture2D> GLFrameBuffer::getDepthAttachment()
{
    return depthAttachment;
}

void GLFrameBuffer::addColorAttachment()
{
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

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)size.x, (GLsizei)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // 设置纹理过滤
        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachment.size(), GL_TEXTURE_2D, attach->getHandle(), 0);

        colorAttachment.push_back(attach);
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

        // 设置纹理过滤
        attach->setMinFilter(Texture2D::Filter::Bilinear);
        attach->setMagFilter(Texture2D::Filter::Bilinear);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, attach->getHandle(), 0);

        depthAttachment = attach;
    }
    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

} // namespace clem