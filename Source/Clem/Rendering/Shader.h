// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <string>
#include <memory>

namespace clem
{

class Shader
{
public:
	static std::shared_ptr<Shader> create(const std::string& vertexSrc, const std::string& fragmentSrc);

	virtual void bind() = 0;
};

} // namespace clem