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

void Mesh::bind()
{
    vertexArray->bind();
}

} // namespace clem