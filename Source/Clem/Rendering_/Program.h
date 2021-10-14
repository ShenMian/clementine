// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <memory>
#include <string>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Program
{
public:
    /**
	 * @brief 创建着色器程序.
	 *
	 * @param name  着色器程序名称. 将通过该名称在指定的目录中寻找对应的着色器文件并加载.
	 */
    static std::shared_ptr<Program> create(const std::string& name);

    Program(const std::string& name);

protected:
    std::string name;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem