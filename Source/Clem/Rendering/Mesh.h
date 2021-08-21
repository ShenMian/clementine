// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/ECS.h"
#include <filesystem>
#include <unordered_map>

#include "Texture2D.h"

namespace clem
{

class Vertex;
class IndexBuffer;
class VertexArray;
class VertexBuffer;

struct Mesh
{
    CLEM_DECLARE_TYPE;

public:
    /**
     * @brief 默认构造函数.
     *
     */
    Mesh() = default;

    /**
     * @brief 构造函数. 从文件载入 3D 模型.
     *
     * @param path 文件路径.
     */
    Mesh(const std::filesystem::path& path);

    /**
     * @brief 从文件载入 3D 模型.
     *
     * @param path 文件路径.
     */
    void load(const std::filesystem::path& path);

    std::filesystem::path        path;
    std::shared_ptr<VertexArray> vertexArray;

private:
    void loadFromFile(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer>  indexBuffer;

    static std::unordered_map<std::filesystem::path, Mesh*> cache;
};

CLEM_DEFINE_TYPE(Mesh);

} // namespace clem