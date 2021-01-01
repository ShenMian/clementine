// Copyright 2020 SMS
// License(Apache-2.0)
// ÓÎÏ·ÊÖ±ú

#ifndef CLEM_INPUT_GAMEPAD_H_
#define CLEM_INPUT_GAMEPAD_H_

#include <vector>
#include "gamepad_event.h"

class Gamepad
{
public:
	enum
	{
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,

		BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_LEFT,
		BUTTON_DPAD_RIGHT,

		BUTTON_LEFT_SHOULDER,
		BUTTON_RIGHT_SHOULDER,

		BUTTON_LEFT_THUMB,
		BUTTON_RIGHT_THUMB,

		AXIS_LEFT_TRIGGER,
		AXIS_RIGHT_TRIGGER,

		JOYSTICK_LEFT_X,
		JOYSTICK_LEFT_Y,
		JOYSTICK_RIGHT_X,
		JOYSTICK_RIGHT_Y,

		BUTTON_START,
		BUTTON_BACK,

		BUTTON_SELECT,
		BUTTON_PAUSE,

		BUTTON_MAX
	};

	Gamepad(short userIndex);
	virtual ~Gamepad();

	void update();

	short getDeviceId() const;
	void  setVibration(unsigned short left, unsigned short right) const;
	
private:
	short userIndex;
	bool  connected;
	bool  keyStatus[BUTTON_MAX];

	void onButton(short keyCode);
	void onAxis(short keyCode, float value);

	static std::vector<Gamepad*> gamepads;
};

#endif // CLEM_INPUT_GAMEPAD_H_
