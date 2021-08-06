// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLVertexArray.h"
#include <glad/glad.h>

namespace clem
{

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &handle);
}

void VertexArray::bind()
{
    glBindVertexArray(handle);
}

void VertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
{
    bind();
    buffer->bind();
    indexBuffer = buffer;
}

void VertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
    bind();
    buffer->bind();
    vertexBuffers.push_back(buffer);
}

} // namespace clem