// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

/**
 * @brief 着色器.
 */
class Shader
{
public:
    enum class Stage
    {
        Vertex,
        Fragment
    };

    enum class Type
    {
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    /**
	 * @brief 创建着色器.
     * 加载对应 SPIR-V 文件， 否则对寻找对应源代码进行编译.
	 *
	 * @param name 着色器名称.
	 */
    static std::shared_ptr<Shader> load(const std::string& name);

    static void                    unload(const std::string& name);
    static void                    reload(const std::string& name);
    static std::shared_ptr<Shader> get(const std::string& name);

    /**
	 * @brief 创建着色器.
	 *
	 * @param vertShader 顶点着色器源文件.
	 * @param fragShader 片段着色器源文件.
	 */
    static std::shared_ptr<Shader> create(const std::filesystem::path& vertShader, const std::filesystem::path& fragShader);

    Shader(const std::string& name);

    virtual void uploadUniform(const std::string& name, const Matrix4& matrix) = 0;
    virtual void uploadUniform(const std::string& name, const Vector3& vector) = 0;
    virtual void uploadUniform(const std::string& name, const Vector2& vector) = 0;
    virtual void uploadUniform(const std::string& name, float value)           = 0;
    virtual void uploadUniform(const std::string& name, int value)             = 0;

    virtual void bind() = 0;

    const std::string& getName() const;

protected:
    std::string name;

    std::unordered_map<Stage, const char*> extensions = {
        {Stage::Vertex, ".vert"},
        {Stage::Fragment, ".frag"}};

private:
    static std::unordered_map<std::string, std::shared_ptr<Shader>> cache;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem

// TODO: 移动到合适的位置
#include <type_traits>

template <typename T, T beginVal, T endVal>
class Iterator
{
    using value_type = std::underlying_type<T>::type;

public:
    Iterator(const T& v)
        : value(static_cast<value_type>(v))
    {
    }

    Iterator()
        : value(static_cast<value_type>(beginVal))
    {
    }

    Iterator begin()
    {
        return *this;
    }

    Iterator end()
    {
        static const Iterator endIter = ++Iterator(endVal);
        return endIter;
    }

    Iterator operator++()
    {
        ++value;
        return *this;
    }

    T operator*()
    {
        return static_cast<T>(value);
    }

    bool operator!=(const Iterator& i)
    {
        return value != i.value;
    }

private:
    value_type value;
};