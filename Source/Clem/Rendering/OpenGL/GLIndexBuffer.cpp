// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLIndexBuffer.h"
#include <glad/glad.h>
#include <type_traits>
#include <unordered_map>

namespace clem
{

static_assert(std::is_same<GLIndexBuffer::handle_type, GLuint>::value);

static std::unordered_map<IndexBuffer::Usage, uint32_t> GLusage = {
    {IndexBuffer::Usage::Static, GL_STATIC_DRAW},
    {IndexBuffer::Usage::Dynamic, GL_DYNAMIC_DRAW},
    {IndexBuffer::Usage::Stream, GL_STREAM_DRAW}};

GLIndexBuffer::GLIndexBuffer(const void* data, size_t size, Usage usage)
{
    size_  = size;
    count_ = size / sizeof(value_type);

    glCreateBuffers(1, &handle);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GLusage[usage]);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &handle);
}

void GLIndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
}

} // namespace clem