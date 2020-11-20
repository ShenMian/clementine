
#include "cursor.h"
#include <stdio.h>
#include <clem/type/point.h>

void Cursor::moveTo(const Point& p) const
{
		printf("\x1b[%d;%dH", (int)p.x, (int)p.y);
}

void Cursor::moveTo(ushort x, ushort y) const
{
	printf("\x1b[%d;%dH", x, y);
}

void Cursor::setVisible(bool v) const
{
	if(v)
		;
	else
		;
}

