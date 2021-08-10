// Copyright 2021 SMS
// License(Apache-2.0)

#include "Module.h"
#include "Assert.hpp"
#include "Core/Math/Math.h"
#include "Logging/Logging.h"
#include "Rendering/Rendering.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

namespace fs = std::filesystem;

namespace clem
{

struct Vertex
{
    Vector3 position;
    Vector3 color;
    Vector3 normal;
    Vector2 uv;
};

void Module::load(std::filesystem::path path)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    std::vector<Vertex> vertices;

    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn, error;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &error, path.string().c_str());
    Assert::isTrue(success && error.empty(), std::format("loading module error: {}", error));
    if(warn.empty())
        CLEM_LOG_WARN("core", std::format("loading module warn: {}", warn));

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
                else
                    vertex.color = {1.f, 1.f, 1.f};
            }

            if(index.normal_index >= 0)
                vertex.normal = {
                    attrib.vertices[3 * index.normal_index + 0],
                    attrib.vertices[3 * index.normal_index + 1],
                    attrib.vertices[3 * index.normal_index + 2]};

            if(index.texcoord_index >= 0)
                vertex.uv = {
                    attrib.vertices[2 * index.texcoord_index + 0],
                    attrib.vertices[2 * index.texcoord_index + 1]};

            vertices.emplace_back(vertex);
        }
    }
}

} // namespace clem