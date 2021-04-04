// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <cstdint>

class Gamepad
{
public:
	enum class Thumb;
	enum class Button : uint16_t;
	enum class Trigger;

	Gamepad(short deviceId = 0);

	void update();

	const Vector2& get(Thumb t) const;
	bool           get(Button b) const;
	uint8_t        get(Trigger t) const;

	/**
	* @brief 设置震动反馈.
	* 
	* @param left  左马达转速.
	* @param right 右马达转速.
	*/
	void setVibration(uint16_t left, uint16_t right);

	bool isConnected() const;

private:
	short deviceId;
	bool  connected = false;

	Vector2  leftThumb;
	Vector2  rightThumb;
	uint16_t buttons      = 0;
	uint8_t  leftTrigger  = 0;
	uint8_t  rightTrigger = 0;
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
