// Copyright 2020 SMS
// License(Apache-2.0)
// ÓÎÏ·ÊÖ±ú

#include "gamepad.h"
#include <assert.h>

#include <windows.h>
#include "xinput.h"

Gamepad::Gamepad(short id)
		: deviceId(id), connected(false)
{
	gamepads.insert({id, this});
}

Gamepad::~Gamepad()
{
	gamepads.erase(deviceId);
}

void Gamepad::update(XINPUT_STATE* state)
{
	static DWORD lastPacketId;
	if(state->dwPacketNumber == lastPacketId)
		return;
	lastPacketId = state->dwPacketNumber;

	
}

void Gamepad::updateAll()
{
	for(short deviceId = 0; deviceId < XUSER_MAX_COUNT; deviceId++)
	{
		XINPUT_STATE state;
		auto         ret = XInputGetState(deviceId, &state);

		if(ret != ERROR_SUCCESS)
			assert(false);
		else if(ret == ERROR_DEVICE_NOT_CONNECTED)
			continue;

		auto it = gamepads.find(deviceId);
		if(it != gamepads.end())
			it->second->update(&state);
		else
			new Gamepad(deviceId);
	}
}
