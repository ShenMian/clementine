﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLIndexBuffer.h"
#include <glad/glad.h>
#include <type_traits>

namespace clem
{

static_assert(std::is_same<GLIndexBuffer::id_type, GLuint>::value);

GLIndexBuffer::GLIndexBuffer(const void* data, size_t size)
{
    glCreateBuffers(1, &handle);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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