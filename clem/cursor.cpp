// Copyright 2020 SMS
// License(Apache-2.0)
// 光标

#include "cursor.h"
#include "platform.h"
#include <stdio.h>
#include <assert.h>
#include <clem/type/point.h>

void Cursor::move(const Point& p)
{ 
	move(p.x, p.y);
}

void Cursor::move(short x, short y)
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

