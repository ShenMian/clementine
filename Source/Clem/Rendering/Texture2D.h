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

/**
 * @brief 纹理.
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
        ClampToEdge
    };

    static std::shared_ptr<Texture2D> create();

    static std::shared_ptr<Texture2D> create(const std::filesystem::path& path);

    /**
     * @brief 从文件载入纹理.
     * 
     * @param path 文件路径.
     */
    virtual void load(const std::filesystem::path& path) = 0;

    /**
     * @brief 从文件载入立方体纹理.
     * 
     * @param faces 6 个面的文件路径.
     * 
     * right, left, top, bottom, back, front
     */
    virtual void loadCubemap(const std::vector<std::filesystem::path>& faces) = 0;

    /**
     * @brief 设置缩小过滤方式.
     * 
     * @param filter 过滤方式.
     */
    virtual void setMinFilter(Filter filter) = 0;

    /**
     * @brief 设置放大过滤方式.
     * 
     * @param filter 过滤方式.
     */
    virtual void setMagFilter(Filter filter) = 0;

    /**
     * @brief 获取纹理大小.
     */
    virtual Size2i getSize() const = 0;

    /**
     * @brief 获取本地句柄.
     */
    virtual size_t getHandle() = 0;

    virtual void bind() = 0;

    virtual void bindUnit(unsigned int slot = 0) = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem
