// Copyright 2021 SMS
// License(Apache-2.0)

#include "Gamepad.h"
#include "Clem/Platform.h"
#include <cassert>
#include <cmath>

Gamepad::Gamepad(short id)
		: deviceId(id)
{
}

const Vector2& Gamepad::get(Thumb t) const
{
	switch(t)
	{
	case Thumb::left:
		return leftThumb;

	case Thumb::right:
		return rightThumb;
	}
	assert(false);
	return Vector2::zero;
}

uint8_t Gamepad::get(Trigger t) const
{
	switch(t)
	{
	case Trigger::left:
		return leftTrigger;

	case Trigger::right:
		return rightTrigger;
	}
	assert(false);
	return 0;
}

bool Gamepad::isConnected() const
{
	return connected;
}

#ifdef OS_WIN

#include <Xinput.h>

constexpr auto leftThumbDeadzone  = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
constexpr auto rightThumbDeadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
constexpr auto leftThumbMax       = 32767;
constexpr auto rightThumbMax      = 32767;
constexpr auto triggerThreshold   = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

void Gamepad::update()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	auto ret = XInputGetState(deviceId, &state);

	if(ret == ERROR_DEVICE_NOT_CONNECTED)
	{
		connected = false;
		return;
	}
	else
		connected = true;
	assert(ret == ERROR_SUCCESS);

	// 按键
	buttons = state.Gamepad.wButtons;

	// 线性按键
	if(state.Gamepad.bLeftTrigger > triggerThreshold)
		leftTrigger = state.Gamepad.bLeftTrigger - triggerThreshold;
	else
		leftTrigger = 0;

	if(state.Gamepad.bRightTrigger > triggerThreshold)
		rightTrigger = state.Gamepad.bRightTrigger - triggerThreshold;
	else
		rightTrigger = 0;

	// 摇杆
	leftThumb.x = state.Gamepad.sThumbLX;
	leftThumb.y = state.Gamepad.sThumbLY;
	if(leftThumb.sizeSquared() > leftThumbDeadzone * leftThumbDeadzone)
	{
		if(leftThumb.sizeSquared() > leftThumbMax * leftThumbMax)
			leftThumb = leftThumb.normalize() * leftThumbMax;
	}
	else
		leftThumb = Vector2::zero;

	rightThumb.x = state.Gamepad.sThumbRX;
	rightThumb.y = state.Gamepad.sThumbRY;
	if(rightThumb.sizeSquared() > rightThumbDeadzone * rightThumbDeadzone)
	{
		if(rightThumb.sizeSquared() > rightThumbMax * rightThumbMax)
			rightThumb = rightThumb.normalize() * rightThumbMax;
	}
	else
		rightThumb = Vector2::zero;
}

bool Gamepad::get(Button b) const
{
	switch(b)
	{
	case Button::A:
		return buttons & XINPUT_GAMEPAD_A;

	case Button::B:
		return buttons & XINPUT_GAMEPAD_B;

	case Button::X:
		return buttons & XINPUT_GAMEPAD_X;

	case Button::Y:
		return buttons & XINPUT_GAMEPAD_Y;

	case Button::Start:
		return buttons & XINPUT_GAMEPAD_START;

	case Button::Back:
		return buttons & XINPUT_GAMEPAD_BACK;

	case Button::DPAD_Up:
		return buttons & XINPUT_GAMEPAD_DPAD_UP;

	case Button::DPAD_Down:
		return buttons & XINPUT_GAMEPAD_DPAD_DOWN;

	case Button::DPAD_Left:
		return buttons & XINPUT_GAMEPAD_DPAD_LEFT;

	case Button::DPAD_Right:
		return buttons & XINPUT_GAMEPAD_DPAD_RIGHT;

	case Button::Shoulder_Left:
		return buttons & XINPUT_GAMEPAD_LEFT_SHOULDER;

	case Button::Shoulder_Right:
		return buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	}
	assert(false);
	return false;
}

void Gamepad::setVibration(uint16_t left, uint16_t right)
{
	XINPUT_VIBRATION v   = {left, right};
	auto             ret = XInputSetState(deviceId, &v);

	if(ret == ERROR_DEVICE_NOT_CONNECTED)
	{
		connected = false;
		return;
	}
	else
		connected = true;
	assert(ret == ERROR_SUCCESS);
}

#endif
