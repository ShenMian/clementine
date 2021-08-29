// Copyright 2021 SMS
// License(Apache-2.0)

#include "Model.h"
#include "Logging/Logging.h"
#include "Profiler.h"

#include "Core/Main.h"
#include "Window/Window.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include <tinygltf/tiny_gltf.h>

namespace fs = std::filesystem;

namespace clem
{

Model::Model(const std::filesystem::path& path, bool compress)
{
    load(path, compress);
}

std::vector<Mesh>& Model::getMeshs()
{
    return meshes;
}

std::vector<Material>& Model::getMaterials()
{
    return materials;
}

const std::vector<Mesh>& Model::getMeshs() const
{
    return meshes;
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

    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", fs::absolute(path).string()));

    clear();
    this->path = fs::relative(path, Application::get().getAssetPath());

    if(path.extension() == ".obj")
        loadObj(path, compress);
    else if(path.extension() == ".gltf" || path.extension() == ".glb")
        loadGltf(path, compress);
    else
        Assert::isTrue(false, "unsupported format");
}

void Model::loadObj(const std::filesystem::path& path, bool compress)
{
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

    auto load = [&](const std::string& name) {
        if(!name.empty())
            return Texture2D::create(path.parent_path() / name);
        return std::shared_ptr<Texture2D>();
    };

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

        auto indexBuffer     = IndexBuffer::create(indices);
        auto vertexBuffer    = VertexBuffer::create(vertices);
        vertexBuffer->layout = {
            {"a_position", Shader::Type::Float3},
            {"a_color", Shader::Type::Float3},
            {"a_normal", Shader::Type::Float3},
            {"a_uv", Shader::Type::Float2}};

        meshes.emplace_back(shape.name, indexBuffer, vertexBuffer);

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

            material.tex.ambient            = load(mat.ambient_texname);
            material.tex.diffuse            = load(mat.diffuse_texname); // FIXME: 可能崩溃
            material.tex.specular           = load(mat.specular_texname);
            material.tex.specular_highlight = load(mat.specular_highlight_texname);
            material.tex.metallic           = load(mat.metallic_texname);
            material.tex.roughness          = load(mat.roughness_texname);
            material.tex.emissive           = load(mat.emissive_texname);
            material.tex.normal             = load(mat.normal_texname);

            if(material.tex.ambient == nullptr)
                material.tex.ambient = material.tex.diffuse;
        }
        materials.push_back(std::move(material));

        indexCount += indexBuffer->count();
        vertexCount += vertexBuffer->count();

        static int  i   = 0; // 调试用. 因为不应该是静态变量
        std::string str = std::format("Importing {}/{}", ++i, shapes.size());
        Main::getWindow()->setTitle(str);
    }
}

static std::unordered_map<int, size_t> GltfComponentLength = {
    {TINYGLTF_TYPE_SCALAR, 1},
    {TINYGLTF_TYPE_VEC2, 2},
    {TINYGLTF_TYPE_VEC3, 3},
    {TINYGLTF_TYPE_VEC4, 4},
    {TINYGLTF_TYPE_MAT2, 4},
    {TINYGLTF_TYPE_MAT3, 9},
    {TINYGLTF_TYPE_MAT4, 16}};

static std::unordered_map<int, size_t> GltfComponentTypeBytes = {
    {TINYGLTF_COMPONENT_TYPE_BYTE, 1},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, 1},
    {TINYGLTF_COMPONENT_TYPE_SHORT, 2},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, 2},
    {TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT, 4},
    {TINYGLTF_COMPONENT_TYPE_FLOAT, 4}};

static std::unordered_map<int, Texture2D::Warp> GltfToWarp = {
    {TINYGLTF_TEXTURE_WRAP_REPEAT, Texture2D::Warp::Repeat},
    {TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE, Texture2D::Warp::ClampToEdge},
    {TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT, Texture2D::Warp::MirrorRepeat}};

static std::unordered_map<int, Texture2D::Filter> GltfToFilter = {
    {TINYGLTF_TEXTURE_FILTER_NEAREST, Texture2D::Filter::Nearest},
    {TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST, Texture2D::Filter::Nearest},
    {TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR, Texture2D::Filter::Nearest},
    {TINYGLTF_TEXTURE_FILTER_LINEAR, Texture2D::Filter::Bilinear},
    {TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST, Texture2D::Filter::Trilinear},
    {TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR, Texture2D::Filter::Trilinear}};

void Model::loadGltf(const std::filesystem::path& path, bool compress)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model    model;
    std::string        error;
    std::string        warn;
    bool               success;

    if(path.extension() == ".gltf")
        success = loader.LoadASCIIFromFile(&model, &error, &warn, path.string());
    else if(path.extension() == ".glb")
        success = loader.LoadBinaryFromFile(&model, &error, &warn, path.string());
    Assert::isTrue(error.empty(), std::format("loading module '{}' error:\n{}", fs::absolute(path).string(), error));
    if(!warn.empty())
        CLEM_LOG_WARN("core", std::format("loading module '{}' warn:\n{}", fs::absolute(path).string(), warn));

    auto load = [&](int index)
    {
        if(index < 0)
            return std::shared_ptr<Texture2D>();
        const auto& tex = model.textures[index];
        if(tex.source != -1)
        {
            const auto& image   = model.images[tex.source];
            auto        texture = Texture2D::create(path.parent_path() / image.uri);
            // auto        texture = Texture2D::create(image.image.data(), {image.width, image.height}, image.bits * image.component);

            if(tex.sampler != -1)
            {
                const auto& sampler = model.samplers[tex.sampler];
                texture->setMinFilter(GltfToFilter[sampler.minFilter]);
                texture->setMagFilter(GltfToFilter[sampler.magFilter]);
                // TODO: 设置环绕方式
            }
            return texture;
        }
        return std::shared_ptr<Texture2D>();
    };

    for(const auto& node : model.nodes)
    {
        if(node.mesh < 0)
            continue;

        const auto& mesh = model.meshes[node.mesh];

        for(const auto& primitive : mesh.primitives)
        {
            const auto& indicesAccessor = model.accessors[primitive.indices];

            std::vector<vertex_type> vertices(indicesAccessor.count);
            std::vector<index_type>  indices(indicesAccessor.count);

            for(const auto& attr : primitive.attributes)
            {
                const auto& accessor   = model.accessors[attr.second];
                const auto& bufferView = model.bufferViews[accessor.bufferView];
                const auto& buffer     = model.buffers[bufferView.buffer];

                const auto comLength       = GltfComponentLength[accessor.type];
                const auto comTypeByteSize = GltfComponentTypeBytes[accessor.componentType];

                const size_t bufferOffset = bufferView.byteOffset + accessor.byteOffset;
                const int    bufferLength = accessor.count * comLength * comTypeByteSize;
                const auto   first        = buffer.data.begin() + bufferOffset;
                const auto   data         = std::vector<uint8_t>(first, first + bufferLength);

                if(attr.first == "POSITION")
                    for(size_t i = 0; i < accessor.count; i++)
                        vertices[i].position = reinterpret_cast<const Vector3*>(data.data())[i];
                else if(attr.first == "NORMAL")
                    for(size_t i = 0; i < accessor.count; i++)
                        vertices[i].normal = reinterpret_cast<const Vector3*>(data.data())[i];
                else if(attr.first == "TEXCOORD_0")
                    for(size_t i = 0; i < accessor.count; i++)
                        vertices[i].uv = reinterpret_cast<const Vector2*>(data.data())[i];
            }

            {
                const auto accessor   = model.accessors[primitive.indices];
                const auto bufferView = model.bufferViews[accessor.bufferView];
                const auto buffer     = model.buffers[bufferView.buffer];

                const auto comLength       = GltfComponentLength[accessor.type];
                const auto comTypeByteSize = GltfComponentTypeBytes[accessor.componentType];

                const size_t bufferOffset = bufferView.byteOffset + accessor.byteOffset;
                const int    bufferLength = accessor.count * comLength * comTypeByteSize;
                const auto   first        = buffer.data.begin() + bufferOffset;
                const auto   data         = std::vector<uint8_t>(first, first + bufferLength);

                size_t indicesCount = accessor.count;
                if(comTypeByteSize == 2)
                {
                    auto in = reinterpret_cast<const uint16_t*>(data.data());
                    for(size_t i = 0; i < accessor.count; i++)
                        indices[i] = (IndexBuffer::value_type)in[i];
                }
                else if(comTypeByteSize == 4)
                {
                    auto in = reinterpret_cast<const uint32_t*>(data.data());
                    for(size_t i = 0; i < accessor.count; i++)
                        indices[i] = (IndexBuffer::value_type)in[i];
                }
            }

            auto indexBuffer     = IndexBuffer::create(indices);
            auto vertexBuffer    = VertexBuffer::create(vertices);
            vertexBuffer->layout = {
                {"a_position", Shader::Type::Float3},
                {"a_color", Shader::Type::Float3},
                {"a_normal", Shader::Type::Float3},
                {"a_uv", Shader::Type::Float2}};

            meshes.emplace_back(mesh.name, indexBuffer, vertexBuffer);

            indexCount += indexBuffer->count();
            vertexCount += vertexBuffer->count();

            const auto& mat = model.materials[primitive.material];
            const auto& pbr = mat.pbrMetallicRoughness;

            Material material;

            material.name     = mat.name;
            material.diffuse  = {(float)pbr.baseColorFactor[0], (float)pbr.baseColorFactor[1], (float)pbr.baseColorFactor[2]};
            material.emission = {(float)mat.emissiveFactor[0], (float)mat.emissiveFactor[1], (float)mat.emissiveFactor[2]};

            material.tex.diffuse  = load(pbr.baseColorTexture.index);
            material.tex.metallic = load(pbr.metallicRoughnessTexture.index);
            material.tex.emissive = load(mat.emissiveTexture.index);
            material.tex.normal   = load(mat.normalTexture.index);

            if(material.tex.ambient == nullptr)
                material.tex.ambient = material.tex.diffuse;

            materials.push_back(std::move(material));
        }

        static int  i   = 0; // 调试用. 因为不应该是静态变量
        std::string str = std::format("Importing {}/{}", ++i, model.meshes.size());
        Main::getWindow()->setTitle(str);
    }
}

void Model::clear()
{
    path        = "";
    indexCount  = 0;
    vertexCount = 0;
    meshes.clear();
    materials.clear();
}

} // namespace clem