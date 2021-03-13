// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#ifndef CLEM_INPUT_KEYBOARD_H_
#define CLEM_INPUT_KEYBOARD_H_

#include "clem/component.h"
#include "clem/platform.h"
#include <functional>
#include <unordered_map>

/// 键盘输入
class Keyboard : public Component
{
public:
  enum class Key;

  Keyboard();

  void update(float) override;
	void bindOnPressed(Key key, std::function<void()> callback);
	void bindOnChanged(Key key, std::function<void(bool)> callback);
	void clear();

private:
	std::unordered_map<Key, std::function<void()>>     onPressed;
	std::unordered_map<Key, std::function<void(bool)>> onChanged;
	std::unordered_map<Key, bool>                      keyStates;
};

#ifdef OS_UNIX
enum class Keyboard::Key
{
	A = 'a',
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	
	left,
	right,
	up,
	down,
};
#endif

#ifdef OS_WIN
#include <windows.h>
enum class Keyboard::Key
{
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	space = VK_SPACE,
	tab   = VK_TAB,
	esc   = VK_ESCAPE,

	end  = VK_END,
	home = VK_HOME,

	left  = VK_LEFT,
	right = VK_RIGHT,
	up    = VK_UP,
	down  = VK_DOWN,

	f1  = VK_F1,
	f2  = VK_F2,
	f3  = VK_F3,
	f4  = VK_F4,
	f5  = VK_F5,
	f6  = VK_F6,
	f7  = VK_F7,
	f8  = VK_F8,
	f9  = VK_F9,
	f10 = VK_F10,
	f11 = VK_F11,
	f12 = VK_F12,
};
#endif

#endif // !CLEM_INPUT_KEYBOARD_H_
