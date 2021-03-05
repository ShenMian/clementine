// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#include "keyboard.h"
#include "clem/platform.h"

void Keyboard::bind(Key key, std::function<void()> callback)
{
	onPressed.insert({key, callback});
}

#ifdef OS_UNIX

Keyboard::Keyboard()
{
}

void Keyboard::update()
{
}

#endif

#ifdef OS_WIN

#include <windows.h>

Keyboard::Keyboard()
{
}

void Keyboard::update()
{
	for(auto& pair : onPressed)
		if(GetAsyncKeyState(static_cast<short>(pair.first)) & 0x8000)
      pair.second();
}

#endif // OS_WIN

