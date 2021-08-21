// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexBuffer.h"
#include <memory>
#include <vector>

namespace clem
{

class VertexArray
{
public:
    static std::shared_ptr<VertexArray> create();

    virtual void setVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;
    virtual void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer)   = 0;

    std::shared_ptr<IndexBuffer>  getIndexBuffer() const;
    std::shared_ptr<VertexBuffer> getVertexBuffer() const;

    virtual void bind() = 0;

protected:
    std::shared_ptr<IndexBuffer>  indexBuffer;
    std::shared_ptr<VertexBuffer> vertexBuffer;
};

} // namespace clem