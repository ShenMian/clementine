// Copyright 2020 SMS
// License(Apache-2.0)
// 字体属性

#ifndef CLEM_COLOR_H_
#define CLEM_COLOR_H_

#include <string>
#include <vector>
#include <unordered_map>

typedef unsigned short ushort;

class Color
{
public:
	Color();
	Color(ushort attr);

	void on() const;
	void off() const;

	void push();
	void pop();

	const std::string& getString() const;

private:
	const std::string* pString;
	std::string compile(ushort attr) const;
	
	static std::unordered_map<ushort, std::string> index;
	static std::vector<const std::string*> stack;
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
	fore_mask = 0x000F,

	back_black  = 0x0010,
	back_red    = 0x0020,
	back_green  = 0x0030,
	back_yellow = 0x0040,
	back_blue   = 0x0050,
	back_purple = 0x0060,
	back_cyan   = 0x0070,
	back_aqua   = back_cyan,
	back_white  = 0x0080,
	back_mask   = 0x00F0,

	style_normal     = 0x0100,
	style_bold       = 0x0200,
	style_underline  = 0x0500,
	style_underscore = style_underline,
	strle_reverse    = 0x0800,
	style_mask       = 0x0F00
};

#endif // CLEM_COLOR_H_


