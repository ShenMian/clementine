// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include "Assert.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <vector>

namespace fs = std::filesystem;

namespace clem
{

static_assert(std::is_same<GLShader::id_type, GLuint>::value);
static_assert(std::is_same<char, GLchar>::value);

static std::unordered_map<Shader::Type, GLenum> GLType = {
    {Shader::Type::Vertex, GL_VERTEX_SHADER},
    {Shader::Type::Fragment, GL_FRAGMENT_SHADER}};

GLShader::GLShader(const std::string& name)
{
    const fs::path assets  = "assets";
    const fs::path shaders = assets / "shaders";
    const fs::path cache   = assets / "cache/shaders";
    if(!fs::exists(shaders))
        fs::create_directories(shaders);
    if(!fs::exists(cache))
        fs::create_directories(cache);

    handle = glCreateProgram();

    for(auto type : Iterator<Type, Type::Vertex, Type::Fragment>())
    {
        fs::path path = shaders / (name + extensions[type]);
        Assert::isTrue(fs::exists(path), "file doesn't exist");
        auto size = fs::file_size(path);

        std::ifstream file(path, std::ios::binary);
        Assert::isTrue(file.is_open(), std::format("can't open file {}", path.filename().string()));

        std::vector<std::byte> buffer;
        buffer.resize(size);
        file.read((char*)buffer.data(), size);
        file.close();

        auto shader = glCreateShader(GLType[type]);
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
        glAttachShader(handle, shader);
    }

    /*
    const char* extension[] = {".vert", ".frag"};
    GLenum      type[]      = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

    std::string sources[2];

    fs::path glslPath = path.filename().string() + ".glsl";
    if(fs::exists(glslPath))
    {
        std::string   source;
        std::ifstream file(glslPath, std::ios::binary);
        if(!file.is_open())
            return;
        source.resize(fs::file_size(glslPath));
        file.read(source.data(), source.size());

        // 拆分顶点着色器源代码与片段着色器源代码
        std::unordered_map<int, std::string> tokens = {
            {0, "#type vertex"},
            {1, "#type fragment"},
            {1, "#type pixel"}};

        size_t begin = 0, currentType;

        size_t           pos = 0, eol;
        std::string_view src(source), line;
        eol = src.find("\r\n", pos);
        do
        {
            line = src.substr(pos, eol - pos);

            for(auto [type, token] : tokens)
            {
                if(line == token)
                {
                    if(begin)
                    {
                        sources[currentType] = source.substr(begin, pos);
                        begin                = 0;
                    }
                    currentType = type;
                    begin       = pos + token.size();
                }
            }

            pos = eol + 2;
            eol = src.find("\r\n", pos);
        } while(eol != std::string::npos);

        if(eol == std::string::npos)
            sources[currentType] = source.substr(begin, pos);
    }
    else
    {
        for(int i = 0; i < 2; i++)
        {
            const fs::path path = name + extension[i];
            Assert::isTrue(fs::exists(path), std::format("file {} and {} doesn't exist", path.string(), glslPath.string()));

            const auto size = fs::file_size(path);

            std::ifstream file(path, std::ios::binary);
            assert(file.is_open());

            sources[i].resize(size / sizeof(std::string::value_type));
            file.read((char*)sources[i].data(), size);
            file.close();
        }
    }

    for(int i = 0; i < 2; i++)
    {
        const fs::path path = cache / (name + extension[i]);
        if(fs::exists(path))
        {
            // 读取 spv
            const auto size = fs::file_size(path);

            std::ifstream file(path, std::ios::binary);
            assert(file.is_open());

            std::vector<std::byte> buffer;
            buffer.resize(size);
            file.read((char*)buffer.data(), size);
            file.close();

            auto shader = glCreateShader(type[i]);
            glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
            glAttachShader(handle, shader);
        }
        else
        {
            // 编译 sources[] 为 spv
            i--;
        }
    }

    handle = glCreateProgram();

    for(int i = 0; i < 2; i++)
    {
        fs::path binary = path.parent_path() / (name + extension[i]);
        assert(fs::exists(binary));
        auto size = fs::file_size(binary);

        std::ifstream file(binary, std::ios::binary);
        assert(file.is_open());

        std::vector<std::byte> buffer;
        buffer.resize(size);
        file.read((char*)buffer.data(), size);
        file.close();

        auto shader = glCreateShader(type[i]);
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
        glAttachShader(handle, shader);
    }
    */
}

GLShader::GLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    GLint success;

    // 编译顶点着色器
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* source = (const GLchar*)vertexSrc.c_str();

    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glDeleteShader(vertexShader);
        handleError("vertex shader compilation failure");
        return;
    }

    // 编译片段着色器
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    source = (const GLchar*)fragmentSrc.c_str();

    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        handleError("fragment shader compilation failure");
        return;
    }

    // 创建程序
    handle = glCreateProgram();

    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);

    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, (int*)&success);
    if(success == GL_FALSE)
    {
        glDeleteProgram(handle);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        handleError("shader link failure");
        return;
    }

    glDetachShader(handle, vertexShader);
    glDetachShader(handle, fragmentShader);
}

GLShader::~GLShader()
{
    glDeleteProgram(handle);
}

void GLShader::bind()
{
    glUseProgram(handle);
}

void GLShader::uploadUniform(const std::string& name, const Matrix4& mat)
{
    auto location = glGetUniformLocation(handle, name.c_str());
    Assert::isTrue(glGetError() == GL_NO_ERROR);
    glUniformMatrix4fv(location, 1, false, mat.data()); // column major: GL_FALSE, row major: GL_TRUE

    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

void GLShader::uploadUniform(const std::string& name, const Vector3& vec)
{
    auto location = glGetUniformLocation(handle, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);

    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

void GLShader::uploadUniform(const std::string& name, const Vector2& vec)
{
    auto location = glGetUniformLocation(handle, name.c_str());
    glUniform2f(location, vec.x, vec.y);

    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

void GLShader::uploadUniform(const std::string& name, float value)
{
    auto location = glGetUniformLocation(handle, name.c_str());
    glUniform1f(location, value);

    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

void GLShader::handleError(const std::string& msg)
{
    // std::vector<char> infoLog(size);

    GLint size = 0;
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &size);
    std::string info(size, '0');
    glGetProgramInfoLog(handle, (GLsizei)info.size(), &size, info.data());
    info.resize(0, size);

    Assert::isTrue(false, std::format("{}: {}", msg, info));
}

} // namespace clem