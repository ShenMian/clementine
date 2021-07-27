// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <memory>
#include <string>

namespace clem
{

class Shader
{
public:
	/**
	 * @brief 创建 Shader.
	 *
	 * @param vertexSrc vertex shader 的源代码.
	 * @param fragmentSrc fragment shader 的源代码.
	 */
	static std::shared_ptr<Shader> create(const std::string& vertexSrc, const std::string& fragmentSrc);

	virtual void bind() = 0;
};

} // namespace clem