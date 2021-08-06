// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <memory>
#include <string>
#include <unordered_map>

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

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
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
	 *
	 * @param name 着色器 SPIR-V 名称.
	 */
    static std::shared_ptr<Shader> create(const std::string& name);

    /**
	 * @brief 创建着色器.
	 *
	 * @param vertexSrc vertex shader 的源代码.
	 * @param fragmentSrc fragment shader 的源代码.
	 */
    static std::shared_ptr<Shader> create(const std::string& vertexSrc, const std::string& fragmentSrc);

    virtual void bind() = 0;

    virtual void uploadUniform(const std::string& name, const Matrix4& matrix) = 0;
    virtual void uploadUniform(const std::string& name, const Vector3& vector) = 0;
    virtual void uploadUniform(const std::string& name, const Vector2& vector) = 0;
    virtual void uploadUniform(const std::string& name, float value)           = 0;

protected:
    std::unordered_map<Stage, const char*> extensions = {
        {Stage::Vertex, ".vert"},
        {Stage::Fragment, ".frag"}};
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem