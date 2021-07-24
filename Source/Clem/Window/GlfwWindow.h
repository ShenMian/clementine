// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "WindowBase.h"
#include <memory>

struct GLFWwindow;

namespace clem
{

class Shader;

/**
 * @brief 窗口.
 */
class GlfwWindow : public WindowBase
{
public:
	/**
	 * @brief 构造函数.
	 *
	 * @param title 窗口标题.
	 * @param size 窗口大小.
	 */
	GlfwWindow(const std::string& title, Size2i size);

	/**
	 * @brief 默认析构函数.
	 */
	~GlfwWindow();

	/**
	 * @brief 更新.
	 *
	 * 轮询事件, 响应窗口事件.
	 */
	void update(Time dt) override;

	/**
	 * @brief 设置终端窗口标题.
	 *
	 * @warn 此函数性能不稳定, 可能造成超高延迟, 不应该频繁调用.
	 */
	void setTitle(const std::string& title) override;

	/**
	 * @brief 设置窗口大小.
	 */
	void setSize(Size2i size) override;

	/**
	 * @brief 获取窗口大小.
	 */
	Size2i getSize() override;

	/**
	 * @brief 设置窗口坐标.
	 *
	 * @param pos 新窗口坐标.
	 */
	void setPosition(Size2i pos) override;

	/**
	 * @brief 获取窗口坐标.
	 *
	 * @return 当前窗口坐标.
	 */
	Size2i getPosition() override;

	/**
	 * @brief 设置窗口可见性.
	 *
	 * @param visible true 为可见, false 为不可见.
	 */
	void setVisible(bool visible) override;

	/**
	 * @brief 获取窗口可见性.
	 *
	 * @return true 为可见, false 为不可见.
	 */
	bool isVisible() override;

	static void init();
	static void deinit();

private:
	void renderGui(Time dt);

	GLFWwindow*             handle;
	std::unique_ptr<Shader> shader;
};

} // namespace clem