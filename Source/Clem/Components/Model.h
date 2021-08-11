// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <filesystem>

namespace clem
{

class IndexBuffer;
class VertexArray;
class VertexBuffer;

struct Model
{
public:
    /**
     * @brief 从文件载入 3D 模型.
     *
     * @param path 文件路径.
     */
    void load(std::filesystem::path path);

    std::shared_ptr<VertexArray> vertexArray;

private:
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer>  indexBuffer;
};

} // namespace clem