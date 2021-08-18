// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/ECS.h"
#include <filesystem>

// 一个模型包含多个 Mesh

namespace clem
{

class IndexBuffer;
class VertexArray;
class VertexBuffer;

struct Model
{
    CLEM_DECLARE_TYPE;

public:
    /**
     * @brief 默认构造函数.
     *
     */
    Model() = default;

    /**
     * @brief 构造函数. 从文件载入 3D 模型.
     *
     * @param path 文件路径.
     */
    Model(const std::filesystem::path& path);

    /**
     * @brief 从文件载入 3D 模型.
     *
     * @param path 文件路径.
     */
    void load(const std::filesystem::path& path);

    std::shared_ptr<VertexArray> vertexArray;

    std::filesystem::path path;

private:
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer>  indexBuffer;
};

CLEM_DEFINE_TYPE(Model);

} // namespace clem