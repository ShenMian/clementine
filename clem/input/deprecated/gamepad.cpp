// Copyright 2021 SMS
// License(Apache-2.0)
// 游戏手柄

#include "gamepad.h"
#include <cmath>
#include <cassert>
#include "clem/platform.h"

#ifdef OS_WIN

#include <windows.h>
#include <xinput.h> // #include "xinput.h"

Gamepad::Gamepad(short index)
		: userIndex(index), connected(false)
{
	for(short i = 0; i < BUTTON_MAX; i++)
		keyStatus[i] = false;

	/*
	XINPUT_CAPABILITIES capabilities;
	ZeroMemory(&capabilities, sizeof(XINPUT_CAPABILITIES));
	auto ret = XInputGetCapabilities(deviceId, 0, &capabilities);
	if(ret != ERROR_SUCCESS)
		assert(false);
	if(capabilities.Type != XINPUT_DEVTYPE_GAMEPAD)
		assert(false); // 设备不是游戏手柄 (可以发生这种情况吗?)
	*/
}

Gamepad::~Gamepad()
{
}

void Gamepad::update()
{
	// 获取手柄数据
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	auto ret = XInputGetState(userIndex, &state);
	if(ret == ERROR_DEVICE_NOT_CONNECTED)
		return; // 设备离线
	if(ret != ERROR_SUCCESS)
		assert(false); // 未知错误 

	// 检测数据是否有更新
	static DWORD lastPacketNum = -1;
	if(state.dwPacketNumber == lastPacketNum)
		return;
	lastPacketNum = state.dwPacketNumber;

	// 按键
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != keyStatus[BUTTON_A])
		onButton(BUTTON_A);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != keyStatus[BUTTON_B])
		onButton(BUTTON_B);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != keyStatus[BUTTON_X])
		onButton(BUTTON_X);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != keyStatus[BUTTON_Y])
		onButton(BUTTON_Y);

	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != keyStatus[BUTTON_DPAD_UP])
		onButton(BUTTON_DPAD_UP);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != keyStatus[BUTTON_DPAD_DOWN])
		onButton(BUTTON_DPAD_DOWN);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != keyStatus[BUTTON_DPAD_LEFT])
		onButton(BUTTON_DPAD_LEFT);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != keyStatus[BUTTON_DPAD_RIGHT])
		onButton(BUTTON_DPAD_RIGHT);

	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != keyStatus[BUTTON_LEFT_THUMB])
		onButton(BUTTON_LEFT_THUMB);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != keyStatus[BUTTON_RIGHT_THUMB])
		onButton(BUTTON_RIGHT_THUMB);

	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != keyStatus[BUTTON_LEFT_SHOULDER])
		onButton(BUTTON_LEFT_SHOULDER);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != keyStatus[BUTTON_RIGHT_SHOULDER])
		onButton(BUTTON_RIGHT_SHOULDER);

	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != keyStatus[BUTTON_START])
		onButton(BUTTON_START);
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != keyStatus[BUTTON_BACK])
		onButton(BUTTON_BACK);

	// 摇杆
	const auto leftThumbDeadzone  = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	const auto rightThumbDeadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	
	const float LX = state.Gamepad.sThumbLX;
	const float LY = state.Gamepad.sThumbLY;
	const float RX = state.Gamepad.sThumbRX;
	const float RY = state.Gamepad.sThumbRY;

	auto leftMagnitude  = std::sqrt(LX * LX + LY * LY);
	auto rightMagnitude = std::sqrt(RX * RX + RY * RY);

	if(leftMagnitude > leftThumbDeadzone)
	{
		if(leftMagnitude > 32767)
			leftMagnitude = 32767;
		leftMagnitude -= leftThumbDeadzone;
		onAxis(BUTTON_LEFT_THUMB, leftMagnitude);
	}

	if(rightMagnitude > rightThumbDeadzone)
	{
		if(rightMagnitude > 32767)
			rightMagnitude = 32767;
		rightMagnitude -= rightThumbDeadzone;
		onAxis(BUTTON_RIGHT_THUMB, rightMagnitude);
	}
}

void Gamepad::setVibration(unsigned short left, unsigned short right) const
{
	XINPUT_VIBRATION v = {left, right};
	XInputSetState(userIndex, &v);
}

#endif // OS_WIN

short Gamepad::getDeviceId() const
{
	return userIndex;
}

void Gamepad::onButton(short keyCode)
{
	keyStatus[keyCode] = !keyStatus[keyCode];
	auto event = new GamepadEvent(GamepadEvent::SubType::button_status_changed, this,
                                keyCode, keyStatus[keyCode]);
}

void Gamepad::onAxis(short keyCode, float value)
{
	auto event = new GamepadEvent(GamepadEvent::SubType::button_status_changed, this,
																keyCode, value);
}
