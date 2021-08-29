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

Mesh::Mesh(std::string name, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VertexBuffer> vertexBuffer)
    : name(name), indexBuffer(indexBuffer), vertexBuffer(vertexBuffer)
{
    vertexArray = VertexArray::create();
    vertexArray->setVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);
}

const std::string& Mesh::getName() const
{
    return name;
}

const fs::path& Mesh::getPath() const
{
    return path;
}

void Mesh::bind()
{
    vertexArray->bind();
}

} // namespace clem