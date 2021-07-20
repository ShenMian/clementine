// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Clem/Window/Window.h"
#include <string>

namespace clem
{

/**
 * @brief 终端窗口.
 */
class WindowsWindow : public Window
{
public:
	void update() override;

	/**
	 * @brief 设置终端窗口标题.
	 *
	 * @warn 此函数性能不稳定, 可能造成超高延迟, 不应该频繁调用.
	 */
	void setTitle(const std::string& title) override;

	/**
	 * @brief 获取终端可见缓冲区大小, 单位: 字符.
	 */
	Size2i getVisibleSize() override;
};

} // namespace clem