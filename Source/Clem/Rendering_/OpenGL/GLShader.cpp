// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include <unordered_map>

namespace clem
{

static std::unordered_map<Shader_::Stage, GLenum> GLStage = {
    {Shader_::Stage::Vertex, GL_VERTEX_SHADER},
    {Shader_::Stage::Geometry, GL_GEOMETRY_SHADER},
    {Shader_::Stage::Fragment, GL_FRAGMENT_SHADER}};

GLShader_::GLShader_(const std::string& name, Stage stage)
    : Shader_(name, stage)
{
    handle = glCreateShader(GLStage[stage]);
}

GLShader_::~GLShader_()
{
    glDeleteShader(handle);
}

} // namespace clem