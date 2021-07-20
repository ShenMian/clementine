// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <string>

/**
 * @brief 窗口.
 */
class Window
{
public:
	virtual void update() = 0;

	/**
	 * @brief 设置终端窗口标题.
	 */
	virtual void setTitle(const std::string& title) = 0;

	/**
	 * @brief 获取终端可见缓冲区大小.
	 */
	virtual Size2i getVisibleSize() = 0;
};
