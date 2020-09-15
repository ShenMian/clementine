// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#include "keyboard_input.h"
#include <time.h>

using std::vector;

#ifdef OS_LINUX

void KeyboardInput::scan()
{
}

#endif // OS_LINUX

#ifdef OS_WIN

#include <windows.h>

void KeyboardInput::scan()
{
	for(auto pair : index)
		if(GetAsyncKeyState(pair.first) & 0x8000)
			events.push_back(pair.second);
}

#endif // OS_WIN
