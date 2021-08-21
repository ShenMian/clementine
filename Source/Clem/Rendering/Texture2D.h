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
    enum class Type
    {
        Diffuse,  // 参与漫反射
        Specular, // 参与镜面反射

        Normals,  // 法线
        Opacity,  // 透明度
        Emissive, // 被加入光照后的结果中
        
        Default = Diffuse
    };

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
        Repeat,       // 重复
        MirrorRepeat, // 镜像重复
        ClampToEdge
    };

    // 像素格式
    enum class Format
    {
        Auto,
        RGBA8,
        RGB8,
        I8
    };

    static std::shared_ptr<Texture2D> create(Type type = Type::Default);
    static std::shared_ptr<Texture2D> create(const std::filesystem::path& path, Type type = Type::Default);

    /**
     * @brief 从文件载入纹理.
     *
     * @param path 文件路径.
     */
    virtual void load(const std::filesystem::path& path, Format format = Format::Auto) = 0;

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

    void setType(Type type);
    Type getType() const;

protected:
    Type type;

    static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture2D>> cache;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem
