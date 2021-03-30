// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

class Input
{
public:
	static void update();

	static void init();
	static void deinit();
};

enum KeyCode
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

	ESCAPE = 0x1B,

	SPACE    = 0x20,
	PRIOR    = 0x21,
	NEXT     = 0x22,
	END      = 0x23,
	HOME     = 0x24,
	LEFT     = 0x25,
	UP       = 0x26,
	RIGHT    = 0x27,
	DOWN     = 0x28,
	SELECT   = 0x29,
	PRINT    = 0x2A,
	EXECUTE  = 0x2B,
	SNAPSHOT = 0x2C,
	INSERT   = 0x2D,
	DELETE_  = 0x2E,

	NUMPAD0   = 0x60,
	NUMPAD1   = 0x61,
	NUMPAD2   = 0x62,
	NUMPAD3   = 0x63,
	NUMPAD4   = 0x64,
	NUMPAD5   = 0x65,
	NUMPAD6   = 0x66,
	NUMPAD7   = 0x67,
	NUMPAD8   = 0x68,
	NUMPAD9   = 0x69,
	MULTIPLY  = 0x6A,
	ADD       = 0x6B,
	SEPARATOR = 0x6C,
	SUBTRACT  = 0x6D,
	DECIMAL   = 0x6E,
	DIVIDE    = 0x6F,
	F1        = 0x70,
	F2        = 0x71,
	F3        = 0x72,
	F4        = 0x73,
	F5        = 0x74,
	F6        = 0x75,
	F7        = 0x76,
	F8        = 0x77,
	F9        = 0x78,
	F10       = 0x79,
	F11       = 0x7A,
	F12       = 0x7B,
	F13       = 0x7C,
	F14       = 0x7D,
	F15       = 0x7E,
	F16       = 0x7F,
	F17       = 0x80,
	F18       = 0x81,
	F19       = 0x82,
	F20       = 0x83,
	F21       = 0x84,
	F22       = 0x85,
	F23       = 0x86,
	F24       = 0x87
};
