﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKShader.h"
#include "Assert.hpp"
#include "VKRenderer.h"
#include <fstream>

namespace fs = std::filesystem;

namespace clem
{

static std::unordered_map<Shader::Type, vk::ShaderStageFlagBits> VKType = {
    {Shader::Type::Vertex, vk::ShaderStageFlagBits::eVertex},
    {Shader::Type::Fragment, vk::ShaderStageFlagBits::eFragment}};

VKShader::VKShader(const std::string& name)
{
    const fs::path assets  = "assets";
    const fs::path shaders = assets / "shaders";
    const fs::path cache   = assets / "cache/shaders";
    if(!fs::exists(shaders))
        fs::create_directories(shaders);
    if(!fs::exists(cache))
        fs::create_directories(cache);

    fs::path path = name;

    vk::PipelineShaderStageCreateInfo shaderStages[2];
    shaderStages[0] = createShaderStage(path / extensions[Type::Vertex], Type::Vertex);
    shaderStages[1] = createShaderStage(path / extensions[Type::Fragment], Type::Fragment);

    vk::PipelineVertexInputStateCreateInfo vertexInputInfo;

    vk::GraphicsPipelineCreateInfo pipelineInfo;
    pipelineInfo.stageCount        = 2;
    pipelineInfo.pStages           = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    // ...


    try
    {
        VKRenderer::get().device().createGraphicsPipeline(nullptr, pipelineInfo);
    }
    catch(const std::exception& e)
    {
        Assert::isTrue(false, std::format("create graphics pipeline: {}", e.what()));
    }
}

VKShader::VKShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    Assert::isTrue(false);
}

VKShader::~VKShader()
{
}

void VKShader::bind()
{
}

void VKShader::uploadUniform(const std::string& name, const Matrix4& matrix)
{
}

void VKShader::uploadUniform(const std::string& name, const Vector3& vector)
{
}

void VKShader::uploadUniform(const std::string& name, const Vector2& vector)
{
}

void VKShader::uploadUniform(const std::string& name, float value)
{
}

vk::PipelineShaderStageCreateInfo VKShader::createShaderStage(const std::filesystem::path& path, Type type)
{
    Assert::isTrue(fs::exists(path), "file doesn't exist");
    auto size = fs::file_size(path);

    std::ifstream file(path, std::ios::binary);
    Assert::isTrue(file.is_open(), std::format("can't open file {}", path.filename().string()));

    std::vector<std::byte> code;
    code.resize(size);
    file.read((char*)code.data(), size);
    file.close();

    auto module = createShaderModule(code);

    vk::PipelineShaderStageCreateInfo shaderInfo;
    shaderInfo.module = module;
    shaderInfo.pName  = "main";
    shaderInfo.stage  = VKType[type];
    
    return shaderInfo;
}

vk::ShaderModule VKShader::createShaderModule(const std::vector<std::byte>& code)
{
    auto& device = VKRenderer::get().device;

    vk::ShaderModuleCreateInfo moduleInfo;
    moduleInfo.codeSize = code.size();
    moduleInfo.pCode    = (const uint32_t*)code.data();

    vk::ShaderModule shaderModule;
    try
    {
        shaderModule = device().createShaderModule(moduleInfo);
    }
    catch(const std::exception& e)
    {
        Assert::isTrue(false, std::format("create shader module faild: {}", e.what()));
    }

    return shaderModule;
}

} // namespace clem