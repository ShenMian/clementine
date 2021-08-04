// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <filesystem>
#include <memory>
#include <string>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Shader
{
public:
    /**
	 * @brief 创建着色器.
	 *
	 * @param vertexSrc vertex shader 的源代码.
	 * @param fragmentSrc fragment shader 的源代码.
	 */
    static std::shared_ptr<Shader> create(const std::string& vertexSrc, const std::string& fragmentSrc);

    /**
	 * @brief 创建着色器.
	 *
	 * @param path 着色器源代码文件路径.
	 */
    static std::shared_ptr<Shader> create(const std::filesystem::path& path);

    virtual void bind() = 0;

    virtual void uploadUniform(const std::string& name, const Matrix4& matrix) = 0;
    virtual void uploadUniform(const std::string& name, const Vector3& vector) = 0;
    virtual void uploadUniform(const std::string& name, const Vector2& vector) = 0;
    virtual void uploadUniform(const std::string& name, float value) = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem