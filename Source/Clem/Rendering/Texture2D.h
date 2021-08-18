// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <filesystem>
#include <memory>
#include <vector>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Texture2D
{
public:
    // 纹理过滤方式
    enum class Filter
    {
        Nearest, // 最近点采样
        Linear   // 线性纹理过滤, 双线性过滤
    };

    // 纹理环绕方式
    enum class Warp
    {
        Repeat,       // 重复
        MirrorRepeat, // 镜像重复
        ClampToDege
    };

    static std::shared_ptr<Texture2D> create(const std::filesystem::path& path);

    virtual void load(const std::filesystem::path& path)                      = 0;

    // right, left, top, bottom, back, front
    virtual void loadCubemap(const std::vector<std::filesystem::path>& faces) = 0;

    virtual Size2i getSize() const = 0;
    virtual size_t getHandle()     = 0;

    virtual void bind(unsigned int slot = 0) = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem
