// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <memory>
#include <string>

class Vector2;
class Vector3;
class Vector4;
class Matrix4;

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

/**
 * @brief 着色器.
 */
class Shader_
{
public:
    enum class Stage
    {
        Vertex,
        Geometry,
        Fragment,
        Pixel = Fragment
    };

    /**
	 * @brief 创建着色器.
	 *
	 * @param name  着色器名称.
     * @param stage 着色器阶段.
	 */
    static std::shared_ptr<Shader_> create(const std::string& name, Stage stage);

    /**
     * @brief 构造函数.
     * 
	 * @param name  着色器名称.
     * @param stage 着色器阶段.
     */
    Shader_(const std::string& name, Stage stage);

    /**
     * @brief 设置名称.
     * 
     * @param name 名称.
     */
    void setName(const std::string& name);

    /**
     * @brief 获取名称.
     */
    const std::string& getName() const;

    /*
    virtual void uploadUniform(const std::string& name, int value)             = 0;
    virtual void uploadUniform(const std::string& name, float value)           = 0;
    virtual void uploadUniform(const std::string& name, const Vector2& vector) = 0;
    virtual void uploadUniform(const std::string& name, const Vector3& vector) = 0;
    virtual void uploadUniform(const std::string& name, const Vector4& vector) = 0;
    virtual void uploadUniform(const std::string& name, const Matrix4& matrix) = 0;

    virtual void bind() = 0;
    */

protected:
    std::string name;
    Stage       stage;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem