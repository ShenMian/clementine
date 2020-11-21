// Copyright 2020 SMS
// License(Apache-2.0)
// 字体属性

#ifndef CLEM_COLOR_H_
#define CLEM_COLOR_H_

#include <string>
#include <vector>
#include <unordered_map>

class Color
{
public:
	enum class attr;

	Color();
	Color(attr fore);
	Color(attr fore, attr back /*, attr style*/);

	const std::string& getString() const;

private:
	char* fore;
	char* back;
};

enum class Color::attr
{
	black,
	red,
	green,
	yellow,
	blue,
	purple,
	cyan,
	aqua = cyan,
	white,
	max,
};

#endif // CLEM_COLOR_H_
