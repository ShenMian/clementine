// Copyright 2021 SMS
// License(Apache-2.0)

#include "Model.h"
#include "Assert.hpp"
#include "Logging/Logging.h"
#include "Rendering/Rendering.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

namespace fs = std::filesystem;

namespace clem
{

void Model::load(std::filesystem::path path)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      warn, error;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &error, path.string().c_str());
    Assert::isTrue(success && error.empty(), std::format("loading module error: {}", error));
    if(warn.empty())
        CLEM_LOG_WARN("core", std::format("loading module warn: {}", warn));

    std::unordered_map<Vertex, unsigned int> uniqueVertices;
    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            Vertex vertex;

            if(index.vertex_index >= 0)
            {
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
            }

            if(index.normal_index >= 0)
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]};

            if(index.texcoord_index >= 0)
                vertex.uv = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]};

            if(uniqueVertices.count(vertex) == 0)
            {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }
            indices.push_back(uniqueVertices[vertex]);
        }
    }

    vertexBuffer         = VertexBuffer::create(vertices.data(), vertices.size() * sizeof(vertices[0]));
    vertexBuffer->layout = {
        {"a_Position", Shader::Type::Float3},
        {"a_Color", Shader::Type::Float3},
        {"a_Normal", Shader::Type::Float3},
        {"a_Uv", Shader::Type::Float2}};
    indexBuffer = IndexBuffer::create(indices.data(), indices.size() * sizeof(indices[0]));
    vertexArray = VertexArray::create();
    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);
}

} // namespace clem