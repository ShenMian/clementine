// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering.h"
#include <filesystem>

// TODO: 内存管理. std::shared_ptr<ModelData>

namespace clem
{

/**
 * @brief 3D 模型.
 */
class Model
{
    CLEM_DECLARE_TYPE;

public:
    using index_type  = IndexBuffer::value_type;
    using vertex_type = VertexBuffer::value_type;

    Model() = default;
    Model(const std::filesystem::path& path, bool compress = false);

    void load(const std::filesystem::path& path, bool compress = false);

    void clear();

    std::vector<Mesh>&           getMeshs();
    std::vector<Material>&       getMaterials();
    const std::vector<Mesh>&     getMeshs() const;
    const std::vector<Material>& getMaterials() const;
    const std::filesystem::path& getPath() const;
    size_t                       getIndexCount() const;
    size_t                       getVertexCount() const;

private:
    void loadObj(const std::filesystem::path& path, bool compress);
    void loadGltf(const std::filesystem::path& path, bool compress);

    std::vector<Mesh>     meshes;
    std::vector<Material> materials;
    size_t                indexCount  = 0;
    size_t                vertexCount = 0;

    std::filesystem::path path;
};

CLEM_DEFINE_TYPE(Model);

} // namespace clem