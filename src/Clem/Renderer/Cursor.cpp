// Copyright 2021 SMS
// License(Apache-2.0)

#include "Cursor.h"
#include <stdio.h>

void Cursor::move(const Point<float>& p)
{
  move(p.x, p.y);
}

void Cursor::move(short x, short y)
{
  printf("\x1b[%d;%dH", y + 1, x + 1);
}

void Cursor::setVisible(bool v)
{
  if(v)
		printf("\x1b[?25h");
	else
		printf("\x1b[?25l");
}
