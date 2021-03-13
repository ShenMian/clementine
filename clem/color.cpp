// Copyright 2021 SMS
// License(Apache-2.0)
// 字体属性

#include "color.h"
#include <cstdio>
#include <cassert>

using std::string;
using std::printf;

Color::Color()
		: Color(Fore::white, Back::black)
{
}

Color::Color(Fore f)
		: Color(f, Back::black)
{
}

Color::Color(Fore f, Back b)
		: fore(f), back(b)
{
}

void Color::on() const
{
	switch(fore)
	{
	case Fore::black:
		printf("\x1b[30m");
		break;

	case Fore::red:
		printf("\x1b[31m");
		break;

	case Fore::green:
		printf("\x1b[32m");
		break;

	case Fore::yellow:
		printf("\x1b[33m");
		break;

	case Fore::blue:
		printf("\x1b[34m");
		break;

	case Fore::purple:
		printf("\x1b[35m");
		break;

	case Fore::cyan:
		printf("\x1b[36m");
		break;

	case Fore::white:
		printf("\x1b[37m");
		break;

	default:
		assert(false); // 无效前景颜色属性
	}

	switch(back)
	{
	case Back::black:
		printf("\x1b[40m");
		break;

	case Back::red:
		printf("\x1b[41m");
		break;

	case Back::green:
		printf("\x1b[42m");
		break;

	case Back::yellow:
		printf("\x1b[43m");
		break;

	case Back::blue:
		printf("\x1b[44m");
		break;

	case Back::purple:
		printf("\x1b[45m");
		break;

	case Back::cyan:
		printf("\x1b[46m");
		break;

	case Back::white:
		printf("\x1b[47m");
		break;

	default:
		assert(false); // 无效背景颜色属性
	}
}
