﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <string>

class Window
{
public:
	/**
	 * @brief 设置终端窗口标题.
	 *
	 * @warn Windows下此函数性能不稳定, 不应该频繁调用
	 */
	static void setTitle(const std::string& title);

	/**
	 * @brief 获取终端窗口大小.
	 */
	static Size2i getSize();
};
