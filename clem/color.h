// Copyright 2020 SMS
// License(Apache-2.0)
// 控制台字体属性

#include <map>
#include <string>

typedef unsigned short ushort;

enum class Fore;
enum class Back;
enum class Mode;

class Color
{
public:
	static Color& instance();

	std::string operator()(Fore f) const;
	std::string operator()(Back b) const;
	std::string operator()(Mode m) const;

private:
	Color();
};

enum class Fore
{
	black,
	red,
	green,
	yellow,
	blue,
	purple,
	cyan,
	aqua = cyan,
	white
};

enum class Back
{
	black,
	red,
	green,
	yellow,
	blue,
	purple,
	cyan,
	aqua = cyan,
	white
};

enum class Mode
{
	normal     = 0,
	bold       = 1,
	underline  = 4,
	underscore = underline,
	reverse    = 7
};
