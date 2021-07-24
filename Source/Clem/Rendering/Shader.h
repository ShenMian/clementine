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
	 * @brief 构造函数.
	 *
	 * @param vertexSrc vertex shader 的源代码.
	 * @param fragmentSrc fragment shader 的源代码.
	 */
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/**
	 * @brief 默认析构函数.
	 */
	~Shader();

	void bind();

private:
	uint32_t program;
};

} // namespace clem