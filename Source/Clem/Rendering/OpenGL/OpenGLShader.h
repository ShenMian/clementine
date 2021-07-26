// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/Shader.h"
#include <string>

namespace clem
{

class OpenGLShader : public Shader
{
public:
	/**
	 * @brief 构造函数.
	 *
	 * @param vertexSrc vertex shader 的源代码.
	 * @param fragmentSrc fragment shader 的源代码.
	 */
	OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/**
	 * @brief 默认析构函数.
	 */
	~OpenGLShader();

	void bind() override;

private:
	unsigned int program;
};

} // namespace clem