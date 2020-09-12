// Copyright 2020 SMS
// License(Apache-2.0)
// 控制台字体属性

#include "color.h"
#include "os.h"
#include <assert.h>

using std::string;
using std::to_string;

Color& Color::instance()
{
	static Color instance;
	return instance;
}

string Color::operator()(Fore f) const
{
	auto attr = static_cast<int>(f);
	assert(attr <= 8);

	return "\x1b[3" + to_string(attr) + "m";
}

string Color::operator()(Back b) const
{
	auto attr = static_cast<int>(b);
	assert(attr <= 8);

	return "\x1b[4" + to_string(attr) + "m";
}

string Color::operator()(Mode m) const
{
	auto attr = static_cast<int>(m);

	return "\x1b[" + to_string(attr) + "m";
}

Color::Color()
{
#ifdef OS_WIN
	// 开启 VT100模式
	DWORD mode;
	GetConsoleMode(hStdOut, &mode);
	SetConsoleMode(hStdOut, mode | 4);
#endif
}
