// Copyright 2020 SMS
// License(Apache-2.0)
// 字体属性

#include "color.h"
#include <cassert>

using std::string;

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
	case Fore::green:
		fore = "\x1b[32m";
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

	default:
		assert(false); // "无效背景颜色属性"
	}
}

std::string Color::getString() const
{
	return string(fore) + string(back);
}
