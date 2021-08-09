// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include <memory>
#include <vector>

namespace clem
{

class GLVertexArray : public VertexArray
{
    using id_type = unsigned int;

public:
    GLVertexArray();
    ~GLVertexArray();

    void bind() override;

    void addVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;
    void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;

    std::shared_ptr<IndexBuffer> getIndexBuffer() const;

private:
    id_type handle;
    size_t  index = 0;
};

} // namespace clem