// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "../Program.h"
#include <unordered_map>

namespace clem
{

class Shader_;

/**
 * @addtogroup Rendering
 * @{
 */

class GLProgram : public Program
{
public:
    explicit GLProgram(const std::string& name);
    virtual ~GLProgram();

    void bind() override;

    void uploadUniform(const std::string& name, int value) override;
    void uploadUniform(const std::string& name, float value) override;
    void uploadUniform(const std::string& name, const Vector2& value) override;
    void uploadUniform(const std::string& name, const Vector3& value) override;
    void uploadUniform(const std::string& name, const Vector4& value) override;
    void uploadUniform(const std::string& name, const Matrix4& value) override;

private:
    int  getUniformLocation(const std::string& name);
    void attach(const std::shared_ptr<Shader_> shader);

    unsigned int handle;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem