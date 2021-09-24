// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include "Core/Assert.hpp"
#include "GLRenderer.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <vector>

namespace fs = std::filesystem;

namespace clem
{

static_assert(std::is_same<GLShader::handle_type, GLuint>::value);
static_assert(std::is_same<char, GLchar>::value);

static std::unordered_map<Shader::Stage, GLenum> GLStage = {
    {Shader::Stage::Vertex, GL_VERTEX_SHADER},
    {Shader::Stage::Fragment, GL_FRAGMENT_SHADER}};

void GLShader::compile(const std::string& name, Stage stage)
{
    const auto assets = Application::get().getAssetPath();
    if(!fs::exists(assets / "shaders"))
        fs::create_directories(assets / "shaders");

    const fs::path path = assets / "shaders" / (name + extensions[stage]);

    auto shader = glCreateShader(GLStage[stage]);

    Assert::isTrue(fs::exists(path), std::format("shader source file doesn't exist: '{}'", fs::absolute(path).string()));
    auto size = fs::file_size(path);

    std::ifstream file(path, std::ios::binary);
    Assert::isTrue(file.is_open(), std::format("can't open file: '{}'", fs::absolute(path).string()));

    std::vector<char> source(size);
    file.read(source.data(), source.size() * sizeof(char));
    file.close();
    source.push_back('\0');

    const auto* ptr = reinterpret_cast<GLchar*>(source.data());
    glShaderSource(shader, 1, &ptr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint size = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, '\0');
        glGetShaderInfoLog(shader, (GLsizei)info.size(), &size, info.data());
        Assert::isTrue(false, std::format("shader compilation failure: {}", info));

        glDeleteShader(shader);
        return;
    }

    glAttachShader(handle, shader);
}

void GLShader::link()
{
    glLinkProgram(handle);

    int success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLint size = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, 0);
        glGetProgramInfoLog(handle, (GLsizei)info.size(), &size, info.data());
        Assert::isTrue(false, std::format("shader link failure: {}", info));

        glDeleteProgram(handle);
        return;
    }
}

GLShader::GLShader(const std::string& name)
{
    const fs::path assets  = Application::get().getAssetPath();
    const fs::path shaders = assets / "shaders";

    if(!fs::exists(shaders))
        fs::create_directories(shaders);

    handle = glCreateProgram();

    for(auto stage : Iterator<Stage, Stage::Vertex, Stage::Fragment>())
        compile(name, stage);
    link();

    /*
    for(auto stage : Iterator<Stage, Stage::Vertex, Stage::Fragment>())
    {
        fs::path path = assets / "cache/shaders" / (name + extensions[stage]);

        // 若未编译则编译
        if(!fs::exists(path))
        {
            compile(name, stage);
        }

        const auto size = fs::file_size(path);

        std::ifstream file(path, std::ios::binary);
        Assert::isTrue(file.is_open(), std::format("can't open file {}", path.filename().string()));

        std::vector<std::byte> buffer(size);
        file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        file.close();

        auto shader = glCreateShader(GLStage[stage]);
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
        glAttachShader(handle, shader);
    }
    */

    /*
    for(auto type : Iterator<Stage, Stage::Vertex, Stage::Fragment>())
    {
        fs::path path = shaders / (name + extensions[type]);
        Assert::isTrue(fs::exists(path), "file doesn't exist");
        auto size = fs::file_size(path);

        std::ifstream file(path, std::ios::binary);
        Assert::isTrue(file.is_open(), std::format("can't open file {}", path.filename().string()));

        std::vector<std::byte> buffer(size);
        file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        file.close();

        auto shader = glCreateShader(GLStage[type]);
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
        glAttachShader(handle, shader);
    }
    */

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

GLShader::GLShader(const std::filesystem::path& vertShader, const std::filesystem::path& fragShader)
{
    std::string vertSrc;
    {
        Assert::isTrue(fs::exists(vertShader), std::format("file doesn't exist: '{}'", fs::absolute(vertShader).string()));
        auto size = fs::file_size(vertShader);

        std::ifstream file(vertShader, std::ios::binary);
        Assert::isTrue(file.is_open(), std::format("can't open file {}", vertShader.filename().string()));

        vertSrc.resize(size);
        file.read(reinterpret_cast<char*>(vertSrc.data()), vertSrc.size());
        file.close();
    }

    std::string fragSrc;
    {
        Assert::isTrue(fs::exists(fragShader), std::format("file doesn't exist: '{}'", fs::absolute(fragShader).string()));
        auto size = fs::file_size(fragShader);

        std::ifstream file(fragShader, std::ios::binary);
        Assert::isTrue(file.is_open(), std::format("can't open file: '{}'", fragShader.filename().string()));

        fragSrc.resize(size);
        file.read(reinterpret_cast<char*>(fragSrc.data()), fragSrc.size());
        file.close();
    }

    loadFromSource(vertSrc, fragSrc);
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
    bind();
    auto location = glGetUniformLocation(handle, name.c_str());
    // Assert::isTrue(location != -1, std::format("uniform '{}' doesn't exist", name));
    glUniformMatrix4fv(location, 1, false, mat.data()); // column major: GL_FALSE, row major: GL_TRUE

    GLCheckError();
}

void GLShader::uploadUniform(const std::string& name, const Vector3& vec)
{
    bind();
    auto location = glGetUniformLocation(handle, name.c_str());
    // Assert::isTrue(location != -1, std::format("uniform '{}' doesn't exist", name));
    glUniform3f(location, vec.x, vec.y, vec.z);

    GLCheckError();
}

void GLShader::uploadUniform(const std::string& name, const Vector2& vec)
{
    bind();
    auto location = glGetUniformLocation(handle, name.c_str());
    // Assert::isTrue(location != -1, std::format("uniform '{}' doesn't exist", name));
    glUniform2f(location, vec.x, vec.y);

    GLCheckError();
}

void GLShader::uploadUniform(const std::string& name, float value)
{
    bind();
    auto location = glGetUniformLocation(handle, name.c_str());
    // Assert::isTrue(location != -1, std::format("uniform '{}' doesn't exist", name));
    glUniform1f(location, value);

    GLCheckError();
}

void GLShader::uploadUniform(const std::string& name, int value)
{
    bind();
    auto location = glGetUniformLocation(handle, name.c_str());
    // Assert::isTrue(location != -1, std::format("uniform '{}' doesn't exist", name));
    glUniform1i(location, value);

    GLCheckError();
}

void GLShader::loadFromSource(const std::string& vertSrc, const std::string& fragSrc)
{
    GLint success;

    // 编译顶点着色器
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* source = (const GLchar*)vertSrc.c_str();

    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint size = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, '\0');
        glGetShaderInfoLog(vertexShader, (GLsizei)info.size(), &size, info.data());
        Assert::isTrue(false, std::format("vertex shader compilation failure: {}", info));

        glDeleteShader(vertexShader);
        return;
    }

    // 编译片段着色器
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    source = (const GLchar*)fragSrc.c_str();

    glShaderSource(fragmentShader, 1, &source, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint size = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, '\0');
        glGetShaderInfoLog(fragmentShader, (GLsizei)info.size(), &size, info.data());
        Assert::isTrue(false, std::format("fragment shader compilation failure: {}", info));

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        return;
    }

    // 创建程序
    handle = glCreateProgram();

    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);

    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLint size = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, 0);
        glGetProgramInfoLog(handle, (GLsizei)info.size(), &size, info.data());
        Assert::isTrue(false, std::format("shader link failure: {}", info));

        glDeleteProgram(handle);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(handle, vertexShader);
    glDetachShader(handle, fragmentShader);
}

} // namespace clem