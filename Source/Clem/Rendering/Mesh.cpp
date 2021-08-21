// Copyright 2021 SMS
// License(Apache-2.0)

#include "Mesh.h"
#include "Assert.hpp"
#include "Logging/Logging.h"
#include "Profiler.h"
#include "Rendering/Rendering.h"
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

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

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
    Assert::isTrue(textures.contains(type));
    return textures.at(type);
}

void Mesh::bind()
{
    vertexArray->bind();
}

void Mesh::loadFromFile(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
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

    std::unordered_map<Vertex, unsigned int> uniqueVertices;
    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            Vertex vertex;

            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]};

            auto colorIndex = 3 * index.vertex_index + 2;
            if(colorIndex < attrib.colors.size())
                vertex.color = {
                    attrib.colors[colorIndex - 2],
                    attrib.colors[colorIndex - 1],
                    attrib.colors[colorIndex - 0]};

            if(index.normal_index >= 0)
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]};

            if(index.texcoord_index >= 0)
                vertex.uv = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]};

#if 0
            // 顶点去重. 可减少内存占用, 但大大降低读取速度. 性能警告.
            if(!uniqueVertices.contains(vertex))
            {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }
            indices.push_back(uniqueVertices[vertex]);
#else
            indices.push_back(vertices.size());
            vertices.push_back(vertex);
#endif
        }
    }
}

} // namespace clem