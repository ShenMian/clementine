// Copyright 2020 SMS
// License(Apache-2.0)
// Windows

#include "windows.h"
#include <assert.h>

#ifdef OS_WIN

HANDLE Windows::hStdOut;

void Windows::initialize()
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD mode;
	if(!GetConsoleMode(hStdOut, &mode))
		assert(false);
	if(!SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) // ¿ªÆô VT100Ä£Ê½
		assert(false);
}

HANDLE Windows::getStdOut()
{
	return hStdOut;
}

#endif // OS_WIN
