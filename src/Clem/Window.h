// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_WINDOW_H_
#define CLEM_WINDOW_H_

#include "Clem/Core/Math/Vector2f.h"
#include <string>

class Window
{
public:
	/**
	 * @brief 获取终端窗口大小.
	 */
  static Size2 getSize();

	/**
	 * @brief 设置终端窗口标题.
	 * 
	 * @warning Windows下此函数性能不稳定, 不应该频繁调用
	 */
  static void setTitle(const std::string& title);
};

#endif // !CLEM_WINDOW_H_
