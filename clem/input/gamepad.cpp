// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏手柄

#include "gamepad.h"
#include <assert.h>
#include "clem/os.h"

#ifdef OS_WIN

#include <windows.h>
#include <xinput.h> // #include "xinput.h"

Gamepad::Gamepad(short id)
		: deviceId(id), connected(false)
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
	auto ret = XInputGetState(deviceId, &state);
	if(ret != ERROR_SUCCESS)
		assert(false);
	else if(ret == ERROR_DEVICE_NOT_CONNECTED)
		assert(false); // 设备离线

	// 检测数据是否有更新
	static DWORD lastPacketNum = -1;
	if(state.dwPacketNumber == lastPacketNum)
		return;
	lastPacketNum = state.dwPacketNumber;

	// 按键状态改变
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
}

void Gamepad::setVibration(unsigned short left, unsigned short right) const
{
	XINPUT_VIBRATION v = {left, right};
	XInputSetState(deviceId, &v);
}

#endif // OS_WIN

short Gamepad::getDeviceId() const
{
	return deviceId;
}

void Gamepad::onButton(short keyCode)
{
	keyStatus[keyCode] = !keyStatus[keyCode];

	auto event = new GamepadEvent(GamepadEvent::SubType::button_status_changed, this);

	event->gamepad   = this;
	event->keyCode   = keyCode;
	event->keyStatus = keyStatus[keyCode];
}
