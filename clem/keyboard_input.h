// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#ifndef CLEM_KEYBOARD_INPUT_H_
#define CLEM_KEYBOARD_INPUT_H_

#include "input.h"

class KeyboardInput : public Input
{
public:
	void scan();
};

#endif // CLEM_KEYBOARD_INPUT_H_
