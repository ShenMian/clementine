// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLVertexBuffer.h"
#include <glad/glad.h>
#include <type_traits>

namespace clem
{

static_assert(std::is_same<GLVertexBuffer::handle_type, GLuint>::value);

GLVertexBuffer::GLVertexBuffer(const std::vector<value_type>& buf)
    : GLVertexBuffer(buf.data(), buf.size() * sizeof(Vertex))
{
}

GLVertexBuffer::GLVertexBuffer(const void* data, size_t size)
{
    glCreateBuffers(1, &handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &handle);
}

void GLVertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, handle);
}

} // namespace clem