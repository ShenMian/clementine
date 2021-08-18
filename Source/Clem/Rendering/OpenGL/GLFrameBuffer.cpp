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

    attachColor();
    attachDepth();
    Assert::isTrue(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    unbind();
}

GLFrameBuffer::~GLFrameBuffer()
{
    glDeleteFramebuffers(1, &handle);
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

void GLFrameBuffer::attachColor()
{
    if(samples > 1)
    {
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorAttachment);

        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, (GLsizei)size.x, (GLsizei)size.y, GL_FALSE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorAttachment, 0);
    }
    else
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D, colorAttachment);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)size.x, (GLsizei)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // 设置纹理过滤
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);
    }
    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

void GLFrameBuffer::attachDepth()
{
    if(samples > 1)
    {
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &depthAttachment);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depthAttachment);
        glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH24_STENCIL8, (GLsizei)size.x, (GLsizei)size.y, false);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, depthAttachment, 0);
    }
    else
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
        glBindTexture(GL_TEXTURE_2D, depthAttachment);

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, (GLsizei)size.x, (GLsizei)size.y);

        // 设置纹理过滤
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);
    }
    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

} // namespace clem