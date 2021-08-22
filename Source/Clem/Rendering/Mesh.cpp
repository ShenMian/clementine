// Copyright 2021 SMS
// License(Apache-2.0)

#include "Mesh.h"
#include "Assert.hpp"
#include "Logging/Logging.h"
#include "Profiler.h"
#include "UI/Browser.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

namespace fs = std::filesystem;

namespace clem
{

std::unordered_map<std::filesystem::path, Mesh*> Mesh::cache;

Mesh::Mesh(const fs::path& path)
{
    load(path);
}

// TODO: 资源管理, 自动释放资源.
void Mesh::load(const fs::path& path)
{
    PROFILE_FUNC();

    this->path = fs::relative(path, ui::Browser::assets);

    std::vector<vertex_type> vertices;
    std::vector<index_type>  indices;

    loadFromFile(path, vertices, indices);

    vertexBuffer         = VertexBuffer::create(vertices.data(), vertices.size() * sizeof(vertices[0]));
    vertexBuffer->layout = {
        {"a_position", Shader::Type::Float3},
        {"a_color", Shader::Type::Float3},
        {"a_normal", Shader::Type::Float3},
        {"a_uv", Shader::Type::Float2}};

    indexBuffer = IndexBuffer::create(indices.data(), indices.size() * sizeof(indices[0]));

    vertexArray = VertexArray::create();
    vertexArray->setVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);

    cache.insert({this->path, this});
}

void Mesh::addTexture(std::shared_ptr<Texture2D> texture)
{
    Assert::isTrue(!textures.contains(texture->getType()));
    textures.insert({texture->getType(), texture});
}

std::shared_ptr<Texture2D> Mesh::getTexture(Texture2D::Type type) const
{
    if(textures.contains(type))
        return textures.at(type);
    else
        return nullptr;
}

void Mesh::bind()
{
    vertexArray->bind();
}

void Mesh::loadFromFile(const std::filesystem::path& path, std::vector<vertex_type>& vertices, std::vector<index_type>& indices)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", fs::absolute(path).string()));

    tinyobj::ObjReaderConfig config;
    tinyobj::ObjReader       reader;

    config.mtl_search_path = path.parent_path().string();

    auto success = reader.ParseFromFile(path.string(), config);
    Assert::isTrue(success, std::format("loading module error: {}", reader.Error()));
    if(!reader.Warning().empty())
        CLEM_LOG_WARN("core", std::format("loading module warn: {}", reader.Warning()));

    auto& attrib    = reader.GetAttrib();
    auto& shapes    = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::unordered_map<Vertex, IndexBuffer::value_type> uniqueVertices;
    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            Vertex vertex;

            vertex.position = {
                attrib.vertices[3 * (size_t)index.vertex_index + 0],
                attrib.vertices[3 * (size_t)index.vertex_index + 1],
                attrib.vertices[3 * (size_t)index.vertex_index + 2]};

            auto colorIndex = 3 * index.vertex_index + 2;
            if(colorIndex < attrib.colors.size())
                vertex.color = {
                    attrib.colors[(size_t)colorIndex - 2],
                    attrib.colors[(size_t)colorIndex - 1],
                    attrib.colors[(size_t)colorIndex - 0]};

            if(index.normal_index >= 0)
                vertex.normal = {
                    attrib.normals[3 * (size_t)index.normal_index + 0],
                    attrib.normals[3 * (size_t)index.normal_index + 1],
                    attrib.normals[3 * (size_t)index.normal_index + 2]};

            if(index.texcoord_index >= 0)
                vertex.uv = {
                    attrib.texcoords[2 * (size_t)index.texcoord_index + 0],
                    attrib.texcoords[2 * (size_t)index.texcoord_index + 1]};

            constexpr bool compress = false;
            if constexpr (compress)
            {
                // 焊接顶点, 性能警告
                if(!uniqueVertices.contains(vertex))
                {
                    if(uniqueVertices.size() >= 1000)
                        uniqueVertices.clear();
                    uniqueVertices[vertex] = static_cast<index_type>(vertices.size());
                    vertices.push_back(vertex);
                }
                indices.push_back(uniqueVertices[vertex]);
            }
            else
            {
                indices.push_back(static_cast<index_type>(vertices.size()));
                vertices.push_back(vertex);
            }
        }
    }
}

} // namespace clem