// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <unordered_map>

/**
 * @brief ����.
 */
class Keyboard
{
public:
	enum class Key : uint8_t;

	/**
	 * @brief ��ȡ����״̬.
	 * 
	 * @param k ����.
	 * @return ��������ʱ���� true.
	 */
	static bool getKeyState(Key k);

	/**
	 * @brief ���ð���״̬.
	 * 
	 * @param k ����.
	 * @param s ״̬, ����Ϊ true.
	 */
	static void setKeyState(Key k, bool s);

private:
	static std::unordered_map<Key, bool> states;
};

enum class Keyboard::Key : uint8_t
{
	A = 0x41, // FIXME, ����д�޷���ʼ��״̬
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
