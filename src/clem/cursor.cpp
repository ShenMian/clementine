// Copyright 2021 SMS
// License(Apache-2.0)
// 光标

#include "cursor.h"
#include "platform.h"
#include "clem/Math/Point.h"
#include <stdio.h>
#include <assert.h>

/**
 * @brief 移动光标到指定坐标
 * 
 * @param p 坐标
 */
void Cursor::move(const Point& p)
{ 
	move(p.x, p.y);
}

/**
 * @brief 移动光标到指定坐标
 * 
 * @param x x坐标
 * @param y y坐标
 */
void Cursor::move(short x, short y)
{
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

/**
 * @brief 设置光标可见性
 * 
 * @param v 可见性
 */
void Cursor::setVisible(bool v)
{
	if(v)
		printf("\x1b[?25h");
	else
		printf("\x1b[?25l");
}

