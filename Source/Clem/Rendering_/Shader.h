// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

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
        Pixel = Fragment,
        Compute
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
     * @brief 获取名称.
     */
    const std::string& getName() const;

    /**
     * @brief 获取阶段.
     */
    Stage getStage() const;

protected:
    std::string name;
    Stage       stage;

    static std::unordered_map<Shader_::Stage, const char*> extension;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem