// Copyright 2020 SMS
// License(Apache-2.0)
// 光标

#include "cursor.h"
#include "platform.h"
#include <stdio.h>
#include <assert.h>
#include <clem/type/point.h>

<<<<<<< HEAD
void Cursor::moveTo(const Point& p)
{ 
	moveTo(p.x, p.y);
=======
void Cursor::move(const Point& p)
{
	move(p.x, p.y);
>>>>>>> f902c4e6f166cfb60f87350bdb490a4d341da57c
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

