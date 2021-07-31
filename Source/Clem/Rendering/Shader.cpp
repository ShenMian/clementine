// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "OpenGL/GLShader.h"

namespace clem
{

std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	return std::make_shared<GLShader>(vertexSrc, fragmentSrc);
}

std::shared_ptr<Shader> Shader::create(const std::filesystem::path& path)
{
	return std::make_shared<GLShader>(path);
}

} // namespace clem