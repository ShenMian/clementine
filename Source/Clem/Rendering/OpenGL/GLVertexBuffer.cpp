// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLVertexBuffer.h"
#include <glad/glad.h>
#include <type_traits>

namespace clem
{

static_assert(std::is_same<GLVertexBuffer::handle_type, GLuint>::value);

static std::unordered_map<VertexBuffer::Usage, uint32_t> GLusage = {
    {VertexBuffer::Usage::Static, GL_STATIC_DRAW},
    {VertexBuffer::Usage::Dynamic, GL_DYNAMIC_DRAW},
    {VertexBuffer::Usage::Stream, GL_STREAM_DRAW}};

GLVertexBuffer::GLVertexBuffer(const void* data, size_t size, Usage usage)
{
    size_  = size;
    count_ = size / sizeof(value_type);

    glCreateBuffers(1, &handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GLusage[usage]);
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