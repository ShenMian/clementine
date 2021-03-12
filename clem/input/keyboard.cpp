// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#include "keyboard.h"
#include "clem/platform.h"

using std::vector;

/**
 * @brief 回调绑定, 当按键处于按下状态
 * 
 * @param key 
 * @param callback 
 */
void Keyboard::bindOnPressed(Key key, std::function<void()> callback)
{
	onPressed[key] = callback;
	onChanged[key] = [](bool) {};
	keyStates[key] = false;
}

/**
 * @brief 回调绑定, 当按键状态发生改变
 * 
 * @param key 
 * @param callback 
 */
void Keyboard::bindOnChanged(Key key, std::function<void(bool)> callback)
{
	onChanged[key] = callback;
	onPressed[key] = []() {};
	keyStates[key] = false;
}

/**
 * @brief 清除回调绑定
 */
void Keyboard::clear()
{
	onChanged.clear();
	keyStates.clear();
}

#ifdef OS_UNIX

#include <unistd.h>
#include <termios.h>
#include <algorithm>

Keyboard::Keyboard()
{
    termios opts;
	tcgetattr(0, &opts);          // grab old terminal i/o settings
	opts.c_lflag &= ~ICANON;      // disable buffered i/o
	opts.c_lflag &= ~ECHO;        // set echo mode
	tcsetattr(0, TCSANOW, &opts); // use these new terminal i/o settings now
}

void Keyboard::update(float)
{
	auto code = getchar();
    auto key  = static_cast<Key>(code);
	if(keyStates.find(key) == keyStates.end())
		return;
	onPressed[key]();
    vector<Key> pressed;
    if(keyStates[key] != true)
    {
        keyStates[key] = true;
        onChanged[key](true);
    }
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
