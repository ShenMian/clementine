// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Program
{
public:
    /**
	 * @brief 创建着色器程序.
	 *
	 * @param name 着色器程序名称. 将通过该名称在指定的目录中寻找对应的着色器文件并加载.
	 */
    static std::shared_ptr<Program> create(const std::string& name);

    explicit Program(const std::string& name);

    virtual void bind() = 0;

    virtual void uploadUniform(const std::string& name, int value)            = 0;
    virtual void uploadUniform(const std::string& name, float value)          = 0;
    virtual void uploadUniform(const std::string& name, const Vector2& value) = 0;
    virtual void uploadUniform(const std::string& name, const Vector3& value) = 0;
    virtual void uploadUniform(const std::string& name, const Vector4& value) = 0;
    virtual void uploadUniform(const std::string& name, const Matrix4& value) = 0;

protected:
    std::string name;

    inline static std::unordered_map<std::string, std::shared_ptr<Program>> cache;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem