
#include "cursor.h"
#include <stdio.h>
#include <clem/type/point.h>

void Cursor::moveTo(const Point& p)
{
		printf("\x1b[%d;%dH", (int)p.x, (int)p.y);
}

void Cursor::moveTo(ushort x, ushort y)
{
	printf("\x1b[%u;%uH", x, y);
}

void Cursor::setVisible(bool v)
{
	// FIXME(SMS): Windowsœ¬Œﬁ–ß
	if(v)
		printf("\e[?25h");
	else
		printf("\e[?25l");
}

