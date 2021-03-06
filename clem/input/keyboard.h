// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#ifndef CLEM_INPUT_KEYBOARD_H_
#define CLEM_INPUT_KEYBOARD_H_

#include <functional>
#include <unordered_map>
#include "input_component.h"
#include "clem/platform.h"

class Keyboard : public InputComponent
{
public:
  enum class Key;

  Keyboard();

  void update() override;
	void bind(Key key, std::function<void(bool)> callback);
	void clear();

private:
	std::unordered_map<Key, std::function<void(bool)>> callbacks;
	std::unordered_map<Key, bool>                      keyStates;
};

#ifdef OS_UNIX
enum class Keyboard::Key
{
};
#endif

#ifdef OS_WIN
#include <windows.h>
enum class Keyboard::Key
{
	/*a = 0x61,
	b = 0x62,
	c = 0x63,
	d = 0x64,
	e = 0x65,
	f = 0x66,
	g = 0x67,
	h = 0x68,
	i = 0x69,
	j = 0x6A,
	k = 0x6B,
	l = 0x6C,
	m = 0x6D,
	n = 0x6E,
	o = 0x6F,
	p = 0x70,
	q = 0x71,
	r = 0x72,
	s = 0x73,
	t = 0x74,
	u = 0x75,
	v = 0x76,
	w = 0x77,
	x = 0x78,
	y = 0x79,
	z = 0x7A,*/

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
