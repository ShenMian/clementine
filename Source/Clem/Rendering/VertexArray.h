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

    virtual void bind() = 0;

    virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;
    virtual void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer)   = 0;

    virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;

protected:
    std::shared_ptr<IndexBuffer>               indexBuffer;
    std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
};

} // namespace clem