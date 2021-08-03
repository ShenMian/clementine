// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <cstdint>
#include <unordered_map>

namespace clem
{
/**
 * @brief 鼠标.
 *
 * @warn 仅支持 Windows 系统
 */
class Mouse
{
public:
	enum class Key : uint8_t;

	static void update();

	/**
	 * @brief 获取按键状态.
	 *
	 * @param k 按键.
	 * @return 按键按下时返回 true.
	 */
	static bool getKeyState(Key k);

	/**
	 * @brief 设置按键状态.
	 *
	 * @param k 按键.
	 * @param s 状态, 按下为 true.
	 */
	static void setKeyState(Key k, bool s);

	static Point2 getPosition();
	static void   setPosition(Point2 p);

private:
	static std::unordered_map<Key, bool> states;
	static Point2                        position;
};

enum class Mouse::Key : uint8_t
{
	left,
	right
};
} // namespace clem
