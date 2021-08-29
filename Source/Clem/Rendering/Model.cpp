// Copyright 2021 SMS
// License(Apache-2.0)

#include "Model.h"
#include "Logging/Logging.h"
#include "Profiler.h"

#include "Core/Main.h"
#include "Window/Window.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

namespace fs = std::filesystem;

namespace clem
{

Model::Model(const std::filesystem::path& path, bool compress)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", fs::absolute(path).string()));
    load(path, compress);
}

std::vector<Mesh>& Model::getMeshs()
{
    return meshs;
}

std::vector<Material>& Model::getMaterials()
{
    return materials;
}

const std::vector<Mesh>& Model::getMeshs() const
{
    return meshs;
}

const std::vector<Material>& Model::getMaterials() const
{
    return materials;
}

const std::filesystem::path& Model::getPath() const
{
    return path;
}

size_t Model::getIndexCount() const
{
    return indexCount;
}

size_t Model::getVertexCount() const
{
    return vertexCount;
}

void Model::load(const std::filesystem::path& path, bool compress)
{
    PROFILE_FUNC();

    Assert::isTrue(path.extension() == ".obj");

    clear();

    this->path = fs::relative(path, Application::get().getAssetPath());

    tinyobj::ObjReaderConfig config;
    tinyobj::ObjReader       reader;

    config.mtl_search_path = path.parent_path().string();

    auto success = reader.ParseFromFile(path.string(), config);
    Assert::isTrue(success, std::format("loading module '{}' error:\n{}", fs::absolute(path).string(), reader.Error()));
    if(!reader.Warning().empty())
        CLEM_LOG_WARN("core", std::format("loading module '{}' warn:\n{}", fs::absolute(path).string(), reader.Warning()));

    auto& shapes = reader.GetShapes();
    auto& attrib = reader.GetAttrib();
    auto& mats   = reader.GetMaterials();

    for(const auto& shape : shapes)
    {
        std::vector<vertex_type> vertices;
        std::vector<index_type>  indices;

        // 加载顶点
        std::unordered_map<Vertex, IndexBuffer::value_type> uniqueVertices;
        for(const auto& index : shape.mesh.indices)
        {
            Vertex vertex;

            vertex.position = {
                attrib.vertices[3 * (size_t)index.vertex_index + 0],
                attrib.vertices[3 * (size_t)index.vertex_index + 1],
                attrib.vertices[3 * (size_t)index.vertex_index + 2]};

            vertex.color = {
                attrib.colors[3 * (size_t)index.vertex_index + 0],
                attrib.colors[3 * (size_t)index.vertex_index + 1],
                attrib.colors[3 * (size_t)index.vertex_index + 2]};

            if(index.normal_index >= 0)
                vertex.normal = {
                    attrib.normals[3 * (size_t)index.normal_index + 0],
                    attrib.normals[3 * (size_t)index.normal_index + 1],
                    attrib.normals[3 * (size_t)index.normal_index + 2]};

            if(index.texcoord_index >= 0)
                vertex.uv = {
                    attrib.texcoords[2 * (size_t)index.texcoord_index + 0],
                    1.f - attrib.texcoords[2 * (size_t)index.texcoord_index + 1]};

            if(compress)
            {
                // 顶点去重 + 顶点焊接, 性能警告
                if(!uniqueVertices.contains(vertex))
                {
                    if(uniqueVertices.size() >= 100)
                        uniqueVertices.clear();
                    uniqueVertices[vertex] = static_cast<index_type>(vertices.size());
                    vertices.push_back(vertex);
                }
                indices.push_back(uniqueVertices[vertex]);
            }
            else
            {
                indices.push_back(static_cast<index_type>(vertices.size()));
                vertices.push_back(std::move(vertex));
            }
        }

        // 加载材质
        Material material;
        if(shape.mesh.material_ids[0] >= 0)
        {
            const auto& mat = mats[shape.mesh.material_ids[0]];

            material.name      = mat.name;
            material.ambient   = {mat.ambient[0], mat.ambient[1], mat.ambient[2]};
            material.diffuse   = {mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]};
            material.specular  = {mat.specular[0], mat.specular[1], mat.specular[2]};
            material.emission  = {mat.emission[0], mat.emission[1], mat.emission[2]};
            material.shininess = mat.shininess;

            if(mat.ambient_texname.size())
                material.tex.ambient = Texture2D::create(path.parent_path() / mat.ambient_texname);

            // FIXME: 可能崩溃
            if(mat.diffuse_texname.size())
                material.tex.diffuse = Texture2D::create(path.parent_path() / mat.diffuse_texname);

            if(mat.specular_texname.size())
                material.tex.specular = Texture2D::create(path.parent_path() / mat.specular_texname);

            if(mat.specular_highlight_texname.size())
                material.tex.specular_highlight = Texture2D::create(path.parent_path() / mat.specular_highlight_texname);

            if(mat.metallic_texname.size())
                material.tex.metallic = Texture2D::create(path.parent_path() / mat.metallic_texname);

            if(mat.roughness_texname.size())
                material.tex.roughness = Texture2D::create(path.parent_path() / mat.roughness_texname);

            if(mat.emissive_texname.size())
                material.tex.emissive = Texture2D::create(path.parent_path() / mat.emissive_texname);

            if(mat.normal_texname.size())
                material.tex.normal = Texture2D::create(path.parent_path() / mat.normal_texname);


            if(material.tex.ambient == nullptr)
                material.tex.ambient = material.tex.diffuse;
        }

        auto indexBuffer     = IndexBuffer::create(indices);
        auto vertexBuffer    = VertexBuffer::create(vertices);
        vertexBuffer->layout = {
            {"a_position", Shader::Type::Float3},
            {"a_color", Shader::Type::Float3},
            {"a_normal", Shader::Type::Float3},
            {"a_uv", Shader::Type::Float2}};

        meshs.emplace_back(shape.name, indexBuffer, vertexBuffer);
        materials.push_back(material);

        indexCount  += indexBuffer->count();
        vertexCount += vertexBuffer->count();

        static int  i   = 0; // 调试用. 因为不应该是静态变量
        std::string str = "Importing " + std::to_string(++i) + "/" + std::to_string(shapes.size()) + " shapes";
        Main::getWindow()->setTitle(str);
    }
}

void Model::clear()
{
    path        = "";
    indexCount  = 0;
    vertexCount = 0;
    meshs.clear();
    materials.clear();
}

} // namespace clem