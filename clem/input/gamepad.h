// Copyright 2020 SMS
// License(Apache-2.0)
// ÓÎÏ·ÊÖ±ú

#ifndef CLEM_GAMEPAD_H_
#define CLEM_GAMEPAD_H_

#include <vector>
#include "gamepad_event.h"

class Gamepad
{
public:
	enum Key
	{
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,

		BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_LEFT,
		BUTTON_DPAD_RIGHT,
		BUTTON_DPAD_CENTER,

		BUTTON_LEFT_SHOULDER,
		BUTTON_RIGHT_SHOULDER,

		BUTTON_LEFT_THUMBSTICK,
		BUTTON_RIGHT_THUMBSTICK,

		AXIS_LEFT_TRIGGER,
		AXIS_RIGHT_TRIGGER,

		JOYSTICK_LEFT_X,
		JOYSTICK_LEFT_Y,
		JOYSTICK_RIGHT_X,
		JOYSTICK_RIGHT_Y,

		BUTTON_START,
		BUTTON_SELECT,
		BUTTON_PAUSE,

		BUTTON_C,
		BUTTON_Z,

		MAX
	};

	Gamepad(short deviceId);
	virtual ~Gamepad();

	void update();

	short getDeviceId() const;
	void  setVibration(unsigned short left, unsigned short right) const;
	
private:
	short deviceId;
	bool  connected;
	bool  wireless;
	bool  keyStatus[Key::MAX];

	GamepadEvent buttonEvent;
	GamepadEvent axisEvent;

	void onButton(short keyCode);
	void onAxis();

	static std::vector<Gamepad*> gamepads;
};

#endif // CLEM_GAMEPAD_H_
