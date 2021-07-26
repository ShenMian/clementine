// Copyright 2021 SMS
// License(Apache-2.0)

#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

#include <type_traits>
static_assert(std::is_same<id_type, GLuint>::value);

namespace clem
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, size_t size)
{
	glCreateBuffers(1, &buffer);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &buffer);
}

void OpenGLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

} // namespace clem