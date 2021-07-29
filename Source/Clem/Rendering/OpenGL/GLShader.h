// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/Shader.h"
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
	 * @param vertexSrc vertex shader 的源代码.
	 * @param fragmentSrc fragment shader 的源代码.
	 */
	GLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/**
	 * @brief 默认析构函数.
	 */
	~GLShader();

	void bind() override;

private:
	id_type handle;
};

} // namespace clem