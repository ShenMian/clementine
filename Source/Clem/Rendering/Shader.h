﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
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
	virtual void uploadUniform(std::string& name, const Matrix4& matrix) = 0;
};

} // namespace clem