// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/ECS.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexBuffer.h"
#include <filesystem>
#include <unordered_map>

#include "Texture2D.h"

namespace clem
{

struct Vertex;
class VertexArray;

/**
 * @brief 网格.
 */
struct Mesh
{
    CLEM_DECLARE_TYPE;

public:
    using index_type  = IndexBuffer::value_type;
    using vertex_type = VertexBuffer::value_type;

    /**
     * @brief 默认构造函数.
     *
     */
    Mesh() = default;

    /**
     * @brief 构造函数.
     *
     * @param indexBuffer  顶点缓冲区.
     * @param vertexBuffer 索引缓冲区.
     */
    Mesh(std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VertexBuffer> vertexBuffer);

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

    void bind();

    std::filesystem::path        path;
    std::shared_ptr<VertexArray> vertexArray;

    void                       addTexture(std::shared_ptr<Texture2D> texture);
    std::shared_ptr<Texture2D> getTexture(Texture2D::Type type) const;

private:
    void loadFromFile(const std::filesystem::path& path, std::vector<vertex_type>& vertices, std::vector<index_type>& indices);

    std::shared_ptr<IndexBuffer>  indexBuffer;
    std::shared_ptr<VertexBuffer> vertexBuffer;

    std::unordered_map<Texture2D::Type, std::shared_ptr<Texture2D>> textures;

    static std::unordered_map<std::filesystem::path, Mesh*> cache;
};

CLEM_DEFINE_TYPE(Mesh);

} // namespace clem