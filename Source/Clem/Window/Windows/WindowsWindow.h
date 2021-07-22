// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Clem/Window/Window.h"
#include "GLFW/glfw3.h"
#include <functional>
#include <string>

namespace clem
{

/**
 * @brief 终端窗口.
 */
class WindowsWindow : public Window
{
public:
	/**
	 * @brief 构造函数.
	 * 
	 * @param title 窗口标题.
	 * @param size 窗口大小.
	 */
	WindowsWindow(std::string title, Size2i size);

	/**
	 * @brief 默认析构函数.
	 */
	~WindowsWindow();

	/**
	 * @brief 更新.
	 * 
	 * 轮询事件, 响应窗口事件.
	 */
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

	virtual void init() override;
	virtual void deinit() override;

	std::function<void(int, int)> onResize;
	std::function<void()>         onClose;

private:
	GLFWwindow* handle;
};

} // namespace clem