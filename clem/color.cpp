// Copyright 2020 SMS
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
{
	fore = back = nullptr;

	switch(f)
	{
	case Fore::black:
		fore = "\x1b[30m";
		break;

	case Fore::red:
		fore = "\x1b[31m";
		break;

	case Fore::green:
		fore = "\x1b[32m";
		break;

	case Fore::yellow:
		fore = "\x1b[33m";
		break;

	case Fore::blue:
		fore = "\x1b[34m";
		break;

	case Fore::purple:
		fore = "\x1b[35m";
		break;

	case Fore::cyan:
		fore = "\x1b[36m";
		break;

	case Fore::white:
		fore = "\x1b[37m";
		break;

	default:
		assert(false); // 无效前景颜色属性
	}

	switch(b)
	{
	case Back::black:
		back = "\x1b[40m";
		break;

	case Back::red:
		back = "\x1b[41m";
		break;

	case Back::green:
		back = "\x1b[42m";
		break;

	case Back::yellow:
		back = "\x1b[43m";
		break;

	case Back::blue:
		back = "\x1b[44m";
		break;

	case Back::purple:
		back = "\x1b[45m";
		break;

	case Back::cyan:
		back = "\x1b[46m";
		break;

	case Back::white:
		back = "\x1b[47m";
		break;

	default:
		assert(false); // 无效背景颜色属性
	}
}

void Color::on() const
{
	printf("%s%s", fore, back);
}

std::string Color::getAnsiCode() const
{
	// TODO(SMS): 存在内存访问BUG
	return string(fore) + string(back);
}
