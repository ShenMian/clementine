// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#include "keyboard.h"
#include "clem/platform.h"

void Keyboard::bind(Key key, std::function<void(bool)> callback)
{
	callbacks[key] = callback;
	keyStates[key] = false;
}

void Keyboard::clear()
{
	callbacks.clear();
	keyStates.clear();
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

Keyboard::Keyboard()
{
}

void Keyboard::update()
{
	for(auto& i : callbacks)
	{
		bool state = GetAsyncKeyState(static_cast<int>(i.first)) & 0x8000;
		if(state == keyStates[i.first])
			continue;
		keyStates[i.first] = state;
		i.second(state);
	}
}

#endif // OS_WIN
