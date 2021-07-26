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
	 * @brief ���캯��.
	 *
	 * @param vertexSrc vertex shader ��Դ����.
	 * @param fragmentSrc fragment shader ��Դ����.
	 */
	OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/**
	 * @brief Ĭ����������.
	 */
	~OpenGLShader();

	void bind() override;

private:
	unsigned int program;
};

} // namespace clem