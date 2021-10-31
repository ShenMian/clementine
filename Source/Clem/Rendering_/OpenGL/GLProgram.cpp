// Copyright 2021 SMS
// License(Apache-2.0)


#include "GLProgram.h"
#include "../Program.h"
#include "Core/Assert.hpp"
#include "GLShader.h"
#include <filesystem>
#include <glad/glad.h>

#include "Rendering/OpenGL/GLRenderer.h"

namespace fs = std::filesystem;

namespace clem
{

GLProgram::GLProgram(const std::string& name)
    : Program(name)
{
    handle = glCreateProgram();

    std::shared_ptr<Shader_> vert, geom, frag, comp;

    if(fs::exists(name + ".vert.spv") || fs::exists(name + ".vert.glsl"))
    {
        vert = Shader_::create(name, Shader_::Stage::Vertex);
        attach(vert);
    }
    if(fs::exists(name + ".geom.spv") || fs::exists(name + ".geom.glsl"))
    {
        geom = Shader_::create(name, Shader_::Stage::Geometry);
        attach(geom);
    }
    if(fs::exists(name + ".frag.spv") || fs::exists(name + ".frag.glsl"))
    {
        frag = Shader_::create(name, Shader_::Stage::Fragment);
        attach(frag);
    }
    if(fs::exists(name + ".comp.spv") || fs::exists(name + ".comp.glsl"))
    {
        comp = Shader_::create(name, Shader_::Stage::Compute);
        attach(comp);
    }
    Assert::isTrue(vert && frag, "program must have vertex shader and fragment shader");

    glLinkProgram(handle);

    // 获取链接结果状态
    int status;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        // 获取报错内容
        int size;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &size);
        std::string info(size, '\0');
        glGetProgramInfoLog(handle, (GLsizei)info.size(), &size, info.data());
        Assert::isTrue(false, std::format("program '{}' link failure: {}", name, info));
    }
}

GLProgram::~GLProgram()
{
    glDeleteProgram(handle);
}

void GLProgram::bind()
{
    glUseProgram(handle);
    GLCheckError();
}

void GLProgram::uploadUniform(const std::string& name, int value)
{
    bind();
    glUniform1i(getUniformLocation(name), value);
    GLCheckError();
}

void GLProgram::uploadUniform(const std::string& name, float value)
{
    bind();
    glUniform1f(getUniformLocation(name), value);
    GLCheckError();
}

void GLProgram::uploadUniform(const std::string& name, const Vector2& value)
{
    bind();
    glUniform2f(getUniformLocation(name), value.x, value.y);
    GLCheckError();
}

void GLProgram::uploadUniform(const std::string& name, const Vector3& value)
{
    bind();
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    GLCheckError();
}

void GLProgram::uploadUniform(const std::string& name, const Vector4& value)
{
    bind();
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    GLCheckError();
}

void GLProgram::uploadUniform(const std::string& name, const Matrix4& value)
{
    bind();
    glUniformMatrix4fv(getUniformLocation(name), 1, false, value.data());
    GLCheckError();
}

int GLProgram::getUniformLocation(const std::string& name)
{
    const auto it = uniformLocations.find(name);
    if(it == uniformLocations.end())
    {
        const auto location = glGetUniformLocation(handle, name.c_str());
        // Assert::isTrue(location != -1, std::format("uniform '{}' doesn't exist", name));
        uniformLocations[name] = location;
        return location;
    }
    return it->second;
}

void GLProgram::attach(const std::shared_ptr<Shader_> shader)
{
    glAttachShader(handle, (GLuint)shader->getNativeHandle());
}

} // namespace clem