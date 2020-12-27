// Copyright 2020 SMS
// License(Apache-2.0)
// ÓÎÏ·ÊÖ±ú

#ifndef CLEM_GAMEPAD_H_
#define CLEM_GAMEPAD_H_

#include <unordered_map>

struct _XINPUT_STATE;
typedef _XINPUT_STATE XINPUT_STATE;

class Gamepad
{
public:
	enum Key
	{
		BUTTON_A,
		BUTTON_B,
		BUTTON_C,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_Z,

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
		BUTTON_PAUSE
	};

	Gamepad(short deviceId);
	virtual ~Gamepad();

	void update(XINPUT_STATE* state);

	void handleButton();
	void handleAxis();
	
private:
	short deviceId;
	bool  connected;

	static std::unordered_map<short, Gamepad*> gamepads;
	static void                                updateAll();
};

#endif // CLEM_GAMEPAD_H_
