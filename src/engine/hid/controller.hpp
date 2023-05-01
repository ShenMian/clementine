// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <bitset>
#include <cstdint>
#include <math/math.hpp>
#include <string>

namespace hid
{

/**
 * @brief 控制器.
 */
class Controller
{
public:
	/**
	 * @brief 摇杆.
	 */
	enum class Thumb : uint8_t
	{
		leftX = 0,
		leftY,
		rightX,
		rightY,

		left  = 0,
		right = 2
	};

	/**
	 * @brief 线性按键.
	 */
	enum class Trigger : uint8_t
	{
		left  = 4, ///< 左侧线性按键, 即 LT.
		right = 5  ///< 右侧线性按键, 即 RT.
	};

	/**
	 * @brief 按键.
	 */
	enum class Button : uint8_t
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,

		LeftBumper  = 4,
		RightBumper = 5,

		Back  = 6,
		Start = 7,
		Guide = 8,

		LeftThumb = 9,
		RighThumb = 10,

		DPAD_Up    = 11,
		DPAD_Right = 12,
		DPAD_Down  = 13,
		DPAD_Left  = 14,

		Cross    = A,
		Circle   = B,
		Square   = X,
		Triangle = Y
	};

	virtual void update() = 0;

	/**
	 * @brief 获取设备名称. 人类可读的, UTF-8 编码.
	 */
	virtual std::string name() const = 0;

	/**
	 * @brief 检查手柄是否处于连接状态.
	 *
	 * @return 是否已连接.
	 */
	virtual bool connected() const = 0;

	/**
	 * @brief 设置震动反馈.
	 *
	 * @param strong_speed 强马达转速.
	 * @param weak_speed   弱马达转速.
	 */
	virtual void vibration(float strong_speed, float weak_speed) = 0;

	/**
	 * @brief 获取摇杆数据.
	 *
	 * @param thumb 摇杆.
	 *
	 * @return 范围: [-1, 1]
	 */
	Vector2f get(Thumb thumb) const noexcept
	{
		Vector2f value = get_raw(thumb);

		float deadzone;
		if(thumb == Thumb::left)
			deadzone = leftThumbDeadzone_;
		else
			deadzone = rightThumbDeadzone_;

		const float factor = 1.f / (1.f - deadzone);

		if(value.norm_sq() > deadzone * deadzone)
		{
			const float magnitude = std::min(value.norm(), 1.f);
			return value.normalized() * ((magnitude - deadzone) * factor);
		}
		else
			return Vector2f(0.f);
	}

	/**
	 * @brief 获取原始摇杆数据.
	 *
	 * @param thumb 摇杆.
	 *
	 * @return 范围: [-1, 1]
	 *
	 * @warning 不建议直接使用.
	 */
	Vector2f get_raw(Thumb thumb) const noexcept
	{
		return {axes_[static_cast<uint8_t>(thumb)], axes_[static_cast<uint8_t>(thumb) + 1]};
	}

	/**
	 * @brief 获取线性按键力度.
	 *
	 * @param trigger 线性按键.
	 *
	 * @return 0 表示没有按下, 范围: [0, 1]
	 */
	float get(Trigger trigger) const noexcept
	{
		const float value  = get_raw(trigger);
		const float factor = 1.f / (1.f - triggerThreshold_);

		if(value > triggerThreshold_)
			return (value - triggerThreshold_) * factor;
		else
			return 0;
	}

	/**
	 * @brief 获取原始线性按键数据.
	 *
	 * @param trigger 线性按键.
	 *
	 * @return 0 表示没有按下, 范围: [0, 1]
	 *
	 * @warning 不建议直接使用.
	 */
	float get_raw(Trigger trigger) const noexcept { return axes_[static_cast<uint8_t>(trigger)]; }

	/**
	 * @brief 获取按键状态.
	 *
	 * @param  button 按键.
	 *
	 * @return 按键是否按下.
	 */
	bool get(Button button) const noexcept { return buttons_[static_cast<uint8_t>(button)]; }

protected:
	std::bitset<15> buttons_;
	float           axes_[6] = {};

	float leftThumbDeadzone_  = 0.1f;
	float rightThumbDeadzone_ = 0.1f;
	float triggerThreshold_   = 0.01f;
};

} // namespace hid
