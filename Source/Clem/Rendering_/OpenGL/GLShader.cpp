// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include "Core/Assert.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <glad/glad.h>
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
    load();
}

GLShader_::~GLShader_()
{
    glDeleteShader(handle);
}

void GLShader_::load()
{
    // 从 SPIR-V 文件载入
    if(fs::exists(std::format("{}.{}.spv", name, extension[stage])))
    {
        const fs::path path = std::format("{}.{}.spv", name, extension[stage]);
        const auto     size = fs::file_size(path);

        std::ifstream file(path, std::ios::binary);
        Assert::isTrue(file.is_open());

        std::vector<std::byte> buffer(size);
        file.read((char*)buffer.data(), size);
        file.close();

        glShaderBinary(1, &handle, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
        glSpecializeShader(handle, "main", 0, nullptr, nullptr); // 指定入口点函数名称

        return;
    }

    // 从源文件载入
    else if(fs::exists(std::format("{}.{}.glsl", name, extension[stage])))
    {
        const fs::path path = std::format("{}.{}.glsl", name, extension[stage]);
        const auto     size = fs::file_size(path);

        std::ifstream file(path, std::ios::binary);
        Assert::isTrue(file.is_open());

        // 读取源代码
        std::string buffer;
        buffer.resize(size);
        file.read((char*)buffer.data(), size);
        file.close();
        buffer += "\0";

        // 编译源代码
        const char* strings = buffer.data();
        glShaderSource(handle, 1, &strings, nullptr);
        glCompileShader(handle);

        // 获取编译结果状态
        int status;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE)
        {
            // 获取报错内容
            int size;
            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &size);
            std::string info(size, '\0');
            glGetShaderInfoLog(handle, (GLsizei)info.size(), &size, info.data());
        }

        return;
    }

    Assert::isTrue(false);
}

size_t GLShader_::getNativeHandle() const
{
    return handle;
}

} // namespace clem