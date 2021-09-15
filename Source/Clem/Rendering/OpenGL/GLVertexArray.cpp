// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLVertexArray.h"
#include "Core/Assert.hpp"
#include <glad/glad.h>
#include <unordered_map>

namespace clem
{

static_assert(std::is_same<GLVertexArray::handle_type, GLuint>::value);

static std::unordered_map<Shader::Type, GLenum> GLType = {
    {Shader::Type::Float, GL_FLOAT},
    {Shader::Type::Float2, GL_FLOAT},
    {Shader::Type::Float3, GL_FLOAT},
    {Shader::Type::Float4, GL_FLOAT},
    {Shader::Type::Mat3, GL_FLOAT},
    {Shader::Type::Mat4, GL_FLOAT},
    {Shader::Type::Int, GL_INT},
    {Shader::Type::Int2, GL_INT},
    {Shader::Type::Int3, GL_INT},
    {Shader::Type::Int4, GL_INT},
    {Shader::Type::Bool, GL_BOOL}};

GLVertexArray::GLVertexArray()
{
    glCreateVertexArrays(1, &handle);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &handle);
}

void GLVertexArray::bind()
{
    glBindVertexArray(handle);

    if(indexBuffer)
        indexBuffer->bind();
    if(vertexBuffer)
        vertexBuffer->bind();
}

void GLVertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
{
    indexBuffer = buffer;
}

void GLVertexArray::setVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
    Assert::isTrue(!buffer->layout.empty(), "buffer has no layout");

    bind();
    buffer->bind();
    vertexBuffer = buffer;

    for(const auto& element : buffer->layout)
    {
        if(element.type != Shader::Type::Mat3 && element.type != Shader::Type::Mat4)
        {
            glEnableVertexAttribArray((GLuint)index);
            glVertexAttribPointer((GLuint)index, (GLint)element.count(), GLType[element.type], element.normalized,
                                  (GLsizei)buffer->layout.stride(), (const void*)element.offset);
            index++;
        }
        else
        {
            // NxN 矩阵分解为 N 个 floatN
            for(size_t i = 0; i < element.count(); i++)
            {
                glEnableVertexAttribArray((GLuint)index);
                glVertexAttribPointer((GLuint)index, (GLint)element.count(), GLType[element.type], element.normalized,
                                      (GLsizei)buffer->layout.stride(), (const void*)(element.offset + sizeof(float) * element.count() * i));
                glVertexAttribDivisor((GLuint)index, 1);
                index++;
            }
        }
    }
}

} // namespace clem