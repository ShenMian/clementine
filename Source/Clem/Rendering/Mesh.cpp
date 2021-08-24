// Copyright 2021 SMS
// License(Apache-2.0)

#include "Mesh.h"
#include "Assert.hpp"
#include "Logging/Logging.h"
#include "Profiler.h"
#include "UI/Browser.h"

namespace fs = std::filesystem;

namespace clem
{

std::unordered_map<std::filesystem::path, Mesh*> Mesh::cache;

Mesh::Mesh(std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VertexBuffer> vertexBuffer)
    : indexBuffer(indexBuffer), vertexBuffer(vertexBuffer)
{
    vertexArray = VertexArray::create();
    vertexArray->setVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);
}

Mesh::Mesh(const fs::path& path)
    : path(fs::relative(path, ui::Browser::assets))
{
    load(path);
}

// TODO: 资源管理, 自动释放资源.
void Mesh::load(const fs::path& path)
{
    PROFILE_FUNC();

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
}

} // namespace clem