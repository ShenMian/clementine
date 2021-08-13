// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Shader.h"
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>
#include <vulkan/vulkan.hpp>

namespace clem
{

class VKShader : public Shader
{
public:
    /**
	 * @brief 构造函数.
     *
	 * @param name 着色器名称.
	 */
    VKShader(const std::string& name);

    /**
	 * @brief 构造函数.
	 *
	 * @param vertexSrc 顶点着色器的源代码.
	 * @param fragmentSrc 片段着色器的源代码.
	 */
    VKShader(const std::string& vertexSrc, const std::string& fragmentSrc);

    /**
	 * @brief 默认析构函数.
	 */
    ~VKShader();

    void bind() override;

    void uploadUniform(const std::string& name, const Matrix4& matrix) override;
    void uploadUniform(const std::string& name, const Vector3& vector) override;
    void uploadUniform(const std::string& name, const Vector2& vector) override;
    void uploadUniform(const std::string& name, float value) override;
    void uploadUniform(const std::string& name, int value) override;

private:
    vk::PipelineShaderStageCreateInfo createShaderStage(const std::filesystem::path& path, Stage type);
    vk::ShaderModule                  createShaderModule(const std::vector<std::byte>& code);

    vk::Pipeline                      pipeline;
    vk::PipelineShaderStageCreateInfo shaderStages[2];
};

} // namespace clem