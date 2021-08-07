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
};

} // namespace clem