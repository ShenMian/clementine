// Copyright 2020 SMS
// License(Apache-2.0)
// 光标

#include "cursor.h"
#include "platform.h"
#include <stdio.h>
#include <assert.h>
#include <clem/type/point.h>

void Cursor::moveTo(const Point& p)
{
	moveTo(p.x, p.y);
}

void Cursor::moveTo(short x, short y)
{
	printf("\x1b[%d;%dH", y, x);
}

void Cursor::setVisible(bool v)
{
	if(v)
		printf("\x1b[?25h");
	else
		printf("\x1b[?25l");
}

/*

#include "windows.h"

void Cursor::moveTo(short x, short y)
{
	SetConsoleCursorPosition(Windows::getStdOut(), {x, y});
}

void Cursor::setVisible(bool v)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	bool                ret;

	ret = GetConsoleCursorInfo(Windows::getStdOut(), &cursorInfo);
	if(!ret)
		assert(false);

	cursorInfo.bVisible = v;

	ret = SetConsoleCursorInfo(Windows::getStdOut(), &cursorInfo);
	if(!ret)
		assert(false);
}

*/
