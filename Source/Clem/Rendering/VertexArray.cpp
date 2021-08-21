// Copyright 2021 SMS
// License(Apache-2.0)

#include "VertexArray.h"
#include "OpenGL/GLVertexArray.h"
#include "Renderer.h"

namespace clem
{

std::shared_ptr<VertexArray> VertexArray::create()
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLVertexArray>();
    }
    return nullptr;
}

std::shared_ptr<IndexBuffer> VertexArray::getIndexBuffer() const
{
    return indexBuffer;
}

std::shared_ptr<VertexBuffer> VertexArray::getVertexBuffer() const
{
    return vertexBuffer;
}

} // namespace clem