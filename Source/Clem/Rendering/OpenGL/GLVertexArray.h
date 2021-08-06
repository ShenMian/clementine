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
    using id_type = unsigned int;

public:
    VertexArray();
    ~VertexArray();

    void bind();

    void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
    void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer);

private:
    id_type                                    handle;
    std::shared_ptr<IndexBuffer>               indexBuffer;
    std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
};

} // namespace clem