﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace clem
{

OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, size_t size)
{
	glCreateBuffers(1, &buffer);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &buffer);
}

void OpenGLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

} // namespace clem