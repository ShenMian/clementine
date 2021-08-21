// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Shader.h"
#include <string>

namespace clem
{

class GLShader : public Shader
{
public:
    using handle_type = unsigned int;

    GLShader(const std::string& name);
    GLShader(const std::filesystem::path& vertShader, const std::filesystem::path& fragShader);

    /**
	 * @brief 默认析构函数.
	 */
    ~GLShader();

    void bind() override;

    void uploadUniform(const std::string& name, const Matrix4& matrix) override;
    void uploadUniform(const std::string& name, const Vector3& vector) override;
    void uploadUniform(const std::string& name, const Vector2& vector) override;
    void uploadUniform(const std::string& name, float value) override;
    void uploadUniform(const std::string& name, int value) override;

private:
    void loadFromSource(const std::string& vertSrc, const std::string& fragSrc);
    void handleError(handle_type handle, const std::string& msg);

    handle_type handle;
};

} // namespace clem