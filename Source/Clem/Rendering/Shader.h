// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <string>

namespace clem
{

class Shader
{
public:
	/**
	 * @brief ���캯��.
	 *
	 * @param vertexSrc vertex shader ��Դ����.
	 * @param fragmentSrc fragment shader ��Դ����.
	 */
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/**
	 * @brief Ĭ����������.
	 */
	~Shader();

	void bind();

private:
	uint32_t program;
};

} // namespace clem