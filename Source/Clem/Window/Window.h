// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <functional>
#include <string>

namespace clem
{

/**
 * @brief 窗口.
 */
class Window
{
public:
	/**
	 * @brief 更新.
	 *
	 * 轮询事件, 响应窗口事件.
	 */
	virtual void update() = 0;

	/**
	 * @brief 设置终端窗口标题.
	 */
	virtual void setTitle(const std::string& title) = 0;

	/**
	 * @brief 获取终端可见缓冲区大小.
	 */
	virtual Size2i getVisibleSize() = 0;

	static void init();
	static void deinit();

	std::function<void(Size2i)> onResize;
	std::function<void()>       onClose;
};

} // namespace clem