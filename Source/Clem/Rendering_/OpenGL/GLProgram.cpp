// Copyright 2021 SMS
// License(Apache-2.0)


#include "GLProgram.h"
#include "GLShader.h"
#include "../Program.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace clem
{

GLProgram::GLProgram(const std::string name)
    : Program(name)
{
    handle = glCreateProgram();

    // .vert.glsl

    if(fs::exists(name + ".vert.spv"))
        Shader_::create(name, Shader_::Stage::Vertex);
    else if(fs::exists(name + ".geom.spv"))
        Shader_::create(name, Shader_::Stage::Geometry);
    else if(fs::exists(name + ".frag.spv"))
        Shader_::create(name, Shader_::Stage::Fragment);
    else if(fs::exists(name + ".comp.spv"))
        Shader_::create(name, Shader_::Stage::Compute);
}

GLProgram::~GLProgram()
{
    glDeleteProgram(handle);
}

} // namespace clem