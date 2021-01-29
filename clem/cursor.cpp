// Copyright 2020 SMS
// License(Apache-2.0)
// ¹â±ê

#include "cursor.h"
#include "platform.h"
#include <stdio.h>
#include <assert.h>
#include <clem/type/point.h>

void Cursor::moveTo(const Point& p)
{
	moveTo(p.x, p.y);
}

#ifdef OS_UNIX

void Cursor::moveTo(short x, short y)
{
	printf("\x1b[%d;%dH", x, y);
}

void Cursor::setVisible(bool v)
{
	if(v)
		printf("\e[?25h");
	else
		printf("\e[?25l");
}

#endif // OS_UNIX

#ifdef OS_WIN

void Cursor::moveTo(ushort x, ushort y)
{
	SetConsoleCursorPosition(hStdOut, {(short)x, (short)y});
}

void Cursor::setVisible(bool v)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	bool                ret;

	ret = GetConsoleCursorInfo(hStdOut, &cursorInfo);
	if(!ret)
		assert(false);

	cursorInfo.bVisible = v;

	ret = SetConsoleCursorInfo(hStdOut, &cursorInfo);
	if(!ret)
		assert(false);
}

#endif
