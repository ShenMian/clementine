// Copyright 2021 SMS
// License(Apache-2.0)

#include "Shader.h"
#include "OpenGL/OpenGLShader.h"

namespace clem
{

std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
}

} // namespace clem
