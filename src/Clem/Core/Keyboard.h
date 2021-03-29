// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <unordered_map>

/**
 * @brief 键盘.
 */
class Keyboard
{
public:
	enum class Key : uint8_t;

	/**
	 * @brief 获取按键状态.
	 * 
	 * @param k 按键.
	 * @return 按键按下时返回 true.
	 */
	static bool getKeyState(Key k);

	/**
	 * @brief 设置按键状态.
	 * 
	 * @param k 按键.
	 * @param s 状态, 按下为 true.
	 */
	static void setKeyState(Key k, bool s);

private:
	static std::unordered_map<Key, bool> states;
};

enum class Keyboard::Key : uint8_t
{
	A = 0x41, // FIXME, 这样写无法初始化状态
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

	Escape = 0x1B,

	Space = 0x20,
	Prior,
	Next,
	End,
	Home,
	Left,
	Up,
	Right,
	Down,
	Select,
	Print,
	Execute,
	Snapshot,
	Insert,
	Delete,
};
