// Copyright 2020 SMS
// License(Apache-2.0)
// �ֱ��¼�

#include "clem/event.h"

class Gamepad;

/// 游戏手柄事件(已弃用)
class GamepadEvent : public Event
{
public:
	enum class SubType
	{
		button_status_changed,
		axis_status_changed
	};

	GamepadEvent(SubType, Gamepad*, short keyCode, bool status);
	GamepadEvent(SubType, Gamepad*, short keyCode, float value);

	SubType  getSubType() const;
	Gamepad* getGamepad() const;

	short getKeyCode() const;

	bool  getKeyStatus() const;
	float getValue() const;

private:
	SubType  subType;
	Gamepad* gamepad;
	short    keyCode;
	bool     status;
	float    value;
};
