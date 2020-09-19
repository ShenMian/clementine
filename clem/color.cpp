// Copyright 2020 SMS
// License(Apache-2.0)
// 控制台字体属性

#include "color.h"
#include "os.h"
#include <assert.h>

using std::map;
using std::string;
using std::to_string;

map<ushort, string> Color::index;

Color::Color(ushort attr)
{
#ifdef OS_WIN
	// 开启 VT100模式
	DWORD mode;
	GetConsoleMode(hStdOut, &mode);
	SetConsoleMode(hStdOut, mode | 4);
#endif

	const auto it = index.find(attr);
	if(it == index.end())
	{
		auto pair = index.insert({attr, compile(attr)});
		pStr = &pair.first->second;
	}
	else
		pStr = &it->second;
}

const string& Color::operator()() const
{
	return *pStr;
}

void Color::on() const
{
	printf("%s", pStr->c_str());
}

void Color::off() const
{
	printf("%s", "\x1b[0m");
}

string Color::compile(ushort attr) const
{
	const auto fore = attr & 0x000f;
	const auto back = (attr & 0x00f0) >> 4;
	const auto mode = (attr & 0x0f00) >> 8;

	string str = "\x1b[";

	if(fore)
		str += '3' + to_string(fore - 1) + ';';
	if(back)
		str += '4' + to_string(back - 1) + ';';
	if(mode)
		str += to_string(mode - 1) + ';';

	if(str.back() == ';')
		str.pop_back();
	str += 'm';
	return str;
}

