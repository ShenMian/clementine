// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Window/WindowBase.h"

namespace clem
{

/**
 * @brief 终端窗口.
 */
class ConsoleWindow : public WindowBase
{
public:
	/**
	 * @brief 构造函数.
	 *
	 * @param title 窗口标题.
	 * @param size 可绘制区域大小, 不一定等于窗口大小.
	 */
	ConsoleWindow(std::string title, Size2i size);

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
	 * @brief 设置终端缓冲区大小, 单位: 字符.
	 *
	 * @warn 不影响终端窗口大小.
	 */
	void setSize(Size2i size) override;

	/**
	 * @brief 获取终端缓冲区大小, 单位: 字符.
	 *
	 * @warn 不代表终端窗口大小.
	 */
	Size2i getSize() override;

	/**
	 * @brief 终端窗口不支持.
	 */
	void setPosition(Size2i pos) override;

	/**
	 * @brief 终端窗口不支持.
	 */
	Size2i getPosition() override;

	/**
	 * @brief 终端窗口不支持.
	 */
	void setVisible(bool visible) override;

	/**
	 * @brief 终端窗口不支持.
	 */
	bool isVisible() override;

	static void init();
	static void deinit();

private:
	Size2i size;
};

} // namespace clem