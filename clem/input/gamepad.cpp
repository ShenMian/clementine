// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏手柄

#include "gamepad.h"
#include <assert.h>

#include <windows.h>
#include <xinput.h> // #include "xinput.h"

Gamepad::Gamepad(short id)
		: deviceId(id), connected(false),
			buttonEvent(GamepadEvent::SubType::button_status_changed, this),
			axisEvent(GamepadEvent::SubType::axis_status_changed, this)
{
	XINPUT_CAPABILITIES capabilities;
	ZeroMemory(&capabilities, sizeof(XINPUT_CAPABILITIES));
	auto ret = XInputGetCapabilities(deviceId, 0, &capabilities);
	if(ret != ERROR_SUCCESS)
		assert(false);

	if(capabilities.Type != XINPUT_DEVTYPE_GAMEPAD)
		assert(false); // 设备不是游戏手柄 (可以发生这种情况吗?)

	// 判断手柄相关属性
	if(capabilities.Flags & XINPUT_CAPS_WIRELESS)
		wireless = true;
	else
		wireless = false;
}

Gamepad::~Gamepad()
{
}

void Gamepad::update()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	auto ret = XInputGetState(deviceId, &state);
	if(ret != ERROR_SUCCESS)
		assert(false);
	else if(ret == ERROR_DEVICE_NOT_CONNECTED)
		return;

	static DWORD lastPacketNum = -1;
	if(state.dwPacketNumber == lastPacketNum)
		return;
	lastPacketNum = state.dwPacketNumber;

	if(state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		onButton(BUTTON_A);
	else if(state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		onButton(BUTTON_B);
}

void Gamepad::setVibration(unsigned short left, unsigned short right) const
{
	XINPUT_VIBRATION v = {left, right};
	XInputSetState(deviceId, &v);
}

short Gamepad::getDeviceId() const
{
	return deviceId;
}

bool Gamepad::isWireless() const
{
	return wireless;
}

void Gamepad::onButton(short keyCode)
{
	keyStatus[keyCode] = !keyStatus[keyCode];
	buttonEvent.gamepad   = this;
	buttonEvent.keyCode   = keyCode;
	buttonEvent.keyStatus = keyStatus[keyCode];
}
