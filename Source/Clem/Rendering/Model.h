// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering.h"
#include <filesystem>

// TODO: ������Դ����. std::shared_ptr<ModelData>

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
    Model(const std::filesystem::path& path);

    void load(const std::filesystem::path& path);

    const std::vector<Mesh>&     getMeshs() const;
    const std::vector<Material>& getMaterials() const;
    const std::filesystem::path& getPath() const;

private:
    std::vector<Mesh>     meshs;
    std::vector<Material> materials;

    std::filesystem::path path;
};

CLEM_DEFINE_TYPE(Model);

} // namespace clem