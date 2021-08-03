// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <cstdint>

namespace clem
{
/**
 * @brief 游戏手柄.
 */
class Gamepad
{
public:
	enum class Thumb;
	enum class Button : uint16_t;
	enum class Trigger;

	/**
	 * @brief 构造函数.
	 *
	 * @param deviceId 手柄设备 ID.
	 */
	Gamepad(short deviceId = 0);

	void update();

	/**
	 * @brief 获取摇杆状态.
	 */
	const Vector2& get(Thumb t) const;

	/**
	 * @brief 获取按键状态.
	 */
	bool get(Button b) const;

	/**
	 * @brief 获取线性按键状态.
	 */
	uint8_t get(Trigger t) const;

	/**
	 * @brief 设置震动反馈.
	 *
	 * @param left  左马达转速.
	 * @param right 右马达转速.
	 */
	void setVibration(uint16_t left, uint16_t right);

	/**
	 * @brief 获取手柄连接状态.
	 *
	 * @warning 连接状态来源于最后一次更新.
	 */
	bool isConnected() const;

private:
	short deviceId;
	bool  connected = false;

	Vector2  leftThumb;
	Vector2  rightThumb;
	uint16_t buttons      = 0;
	uint8_t  leftTrigger  = 0;
	uint8_t  rightTrigger = 0;

	bool check(long);
};

enum class Gamepad::Thumb
{
	left,
	right
};

enum class Gamepad::Button : uint16_t
{
	A,
	B,
	X,
	Y,
	Start,
	Back,

	DPAD_Up,
	DPAD_Down,
	DPAD_Left,
	DPAD_Right,

	Shoulder_Left,
	Shoulder_Right
};

enum class Gamepad::Trigger
{
	left,
	right
};
} // namespace clem
