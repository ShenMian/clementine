// Copyright 2020 SMS
// License(Apache-2.0)
// 控制台字体属性

#ifndef CLEM_COLOR_H_
#define CLEM_COLOR_H_

#include <map>
#include <string>

typedef unsigned short ushort;

class Color
{
public:
	Color(ushort attr);

	const std::string& operator()() const;

	void on() const;
	void off() const;

private:
	ushort attribute;
	static std::map<ushort, std::string> index;
	std::string compile(ushort attr) const;
};

enum
{
	fore_black = 0x0001,
	fore_red,
	fore_green,
	fore_yellow,
	fore_blue,
	fore_purple,
	fore_cyan,
	fore_aqua = fore_cyan,
	fore_white,

	back_black  = 0x0010,
	back_red    = 0x0020,
	back_green  = 0x0030,
	back_yellow = 0x0040,
	back_blue   = 0x0050,
	back_purple = 0x0060,
	back_cyan   = 0x0070,
	back_aqua   = back_cyan,
	back_white  = 0x0080,

	mode_normal     = 0x0000,
	mode_bold       = 0x0100,
	mode_underline  = 0x0400,
	mode_underscore = mode_underline,
	mode_reverse    = 0x0700
};

#endif // CLEM_COLOR_H_
