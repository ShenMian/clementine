// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include <cassert>
#include <filesystem>
#include <format>
#include <fstream>
#include <unordered_map>

namespace fs = std::filesystem;

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

    // 从 SPIR-V 文件载入
    if(fs::exists(std::format("{}.{}.spv", name, extension[stage])))
    {
        const fs::path path = std::format("{}.{}.spv", name, extension[stage]);
        const auto     size = fs::file_size(path);

        std::ifstream file(path, std::ios::binary);
        assert(file.is_open());

        std::vector<std::byte> buffer(size);
        file.read((char*)buffer.data(), size);
        file.close();

        glShaderBinary(1, &handle, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
        glSpecializeShader(handle, "main", 0, nullptr, nullptr); // 指定入口点函数名称
    }
}

GLShader_::~GLShader_()
{
    glDeleteShader(handle);
}

} // namespace clem