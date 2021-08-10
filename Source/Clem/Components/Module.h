// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <filesystem>

namespace clem
{

class IndexBuffer;
class VertexBuffer;

struct Module
{
public:
    /**
     * @brief 从文件载入 3D 模型.
     *
     * @param path 文件路径.
     */
    void load(std::filesystem::path path);

private:
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer>  indexBuffer;
};

} // namespace clem