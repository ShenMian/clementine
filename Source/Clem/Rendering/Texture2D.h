// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <vector>

namespace std
{

template <>
struct hash<std::filesystem::path>
{
    size_t operator()(const std::filesystem::path& path) const
    {
        return std::filesystem::hash_value(path);
    }
};

} // namespace std

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
        Nearest,  // 最近点采样
        Bilinear, // 双线性过滤
        Trilinear // 三线性过滤
    };

    // 纹理环绕方式
    enum class Warp
    {
        Repeat,      // 重复
        ClampToEdge,
        MirrorRepeat // 镜像重复
    };

    // 像素格式
    enum class Format
    {
        Auto,
        RGBA8,
        RGB8,
        RG8,
        R8,
        RGBA16,
        RGB16,
        DepthStencil,
        DepthComponent
    };

    Texture2D() = default;

    /**
     * @brief 创建空纹理.
     */
    static std::shared_ptr<Texture2D> create();

    /**
     * @brief 从文件创建纹理.
     *
     * @param path      文件路径.
     * @param genMipmap 是否生成 mipmap.
     * @param format    像素格式.
     */
    static std::shared_ptr<Texture2D> create(const std::filesystem::path& path, bool genMipmap = true, Format format = Format::Auto);

    /**
     * @brief 从文件创建纹理.
     *
     * @param data      图像数据.
     * @param size      图像宽高.
     * @param bits      像素大小.
     * @param genMipmap 是否生成 mipmap.
     * @param format    像素格式.
	 */
    static std::shared_ptr<Texture2D> create(const void* data, Size2i size, int bits, bool genMipmap = true, Format format = Format::Auto);

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
    virtual size_t getHandle() const = 0;

    virtual void bind(unsigned int slot = 0) const = 0;

protected:
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    std::filesystem::path path;

    static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture2D>> cache;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem
