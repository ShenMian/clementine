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

struct Vertex
{
    Vector3 position;
    Vector3 color;
    Vector3 normal;
    Vector2 uv;

    bool operator==(const Vertex& rhs) const = default;
};

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

template <typename T, typename... Rest>
void hashCombine(std::size_t& seed, const T& v, const Rest&... rest)
{
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hashCombine(seed, rest), ...);
};

} // namespace clem