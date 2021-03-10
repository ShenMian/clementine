// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#include "keyboard.h"
#include "clem/platform.h"

void Keyboard::bindOnPressed(Key key, std::function<void()> fun)
{
	onPressed[key] = fun;
	onChanged[key] = [](bool) {};
	keyStates[key] = false;
}

void Keyboard::bindOnChanged(Key key, std::function<void(bool)> callback)
{
	onChanged[key] = callback;
	onPressed[key] = []() {};
	keyStates[key] = false;
}

void Keyboard::clear()
{
	onChanged.clear();
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
	for(auto& i : keyStates)
	{
		bool state = GetAsyncKeyState(static_cast<int>(i.first)) & 0x8000;
		
		if(state != keyStates[i.first])
		{
			keyStates[i.first] = state;
			onChanged[i.first](state);
		}

		if(state)
		{
			keyStates[i.first] = state;
			onPressed[i.first]();
		}
	}
}

#endif // OS_WIN
