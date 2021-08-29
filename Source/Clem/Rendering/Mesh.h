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

// TODO: 内存管理.

/**
 * @brief 网格.
 */
struct Mesh
{
public:
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
    Mesh(std::string name, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VertexBuffer> vertexBuffer);

    const std::string&           getName() const;
    const std::filesystem::path& getPath() const;

    void bind();

    std::shared_ptr<VertexArray> vertexArray;

private:
    std::string                   name;
    std::filesystem::path         path;
    std::shared_ptr<IndexBuffer>  indexBuffer;
    std::shared_ptr<VertexBuffer> vertexBuffer;

    static std::unordered_map<std::filesystem::path, Mesh*> cache;
};

} // namespace clem