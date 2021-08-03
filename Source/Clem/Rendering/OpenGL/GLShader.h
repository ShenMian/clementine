﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Shader.h"
#include <filesystem>
#include <string>

namespace clem
{

class GLShader : public Shader
{
public:
	using id_type = unsigned int;

	/**
	 * @brief 构造函数.
	 *
	 * @param vertexSrc 顶点着色器的源代码.
	 * @param fragmentSrc 片段着色器的源代码.
	 */
	GLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/**
	 * @brief 构造函数.
	 *
	 * @param path 着色器源代码文件路径.
	 */
	GLShader(const std::filesystem::path& path);

	/**
	 * @brief 默认析构函数.
	 */
	~GLShader();

	void bind() override;
	void uploadUniform(const std::string& name, const Matrix4& matrix) override;

private:
	void handleError(const std::string& msg);

	id_type handle;
};

} // namespace clem