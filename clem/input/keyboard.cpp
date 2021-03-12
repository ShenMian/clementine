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

#include <unistd.h>
#include <termios.h>

Keyboard::Keyboard()
{
	tcgetattr(0, &opts);          // grab old terminal i/o settings
	opts.c_lflag &= ~ICANON;      // disable buffered i/o
	opts.c_lflag &= ~ECHO;        // set echo mode
	tcsetattr(0, TCSANOW, &opts); // use these new terminal i/o settings now
}

void Keyboard::update()
{
	auto key = getchar();
	if(keyStates.find(key) == keyStates.end())
		return;
	for(auto key : keyStatus)
		
	onPressed[i.first]();
}

#endif

#ifdef OS_WIN

Keyboard::Keyboard()
{
}

void Keyboard::update(float)
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
