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
	void on() const;
	void off() const;

private:
	ushort attribute;
	static std::map<ushort, std::string> index;
	std::string compile(ushort attr) const;
};

enum
{
	fore_black,
	fore_red,
	fore_green,
	fore_yellow,
	fore_blue,
	fore_purple,
	fore_cyan,
	fore_aqua = fore_cyan,
	fore_white,
	fore_normal,

	back_black,
	back_red,
	back_green,
	back_yellow,
	back_blue,
	back_purple,
	back_cyan,
	back_aqua = back_cyan,
	back_white,
	back_normal,

	mode_bold       = 1,
	mode_underline  = 4,
	mode_underscore = mode_underline,
	mode_reverse    = 7
};

#endif // CLEM_COLOR_H_
