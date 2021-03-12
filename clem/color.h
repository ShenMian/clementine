// Copyright 2020 SMS
// License(Apache-2.0)
// 字体属性

#ifndef CLEM_COLOR_H_
#define CLEM_COLOR_H_

#include <string>
#include <unordered_map>
#include <vector>

enum class Fore;
enum class Back;

/// 颜色属性
class Color
{
	friend class FrameBuffer;

public:
	enum class Type;

	Color();
	Color(Fore fore);
	Color(Fore fore, Back back);

	void on() const;

private:
	Fore fore;
	Back back;
};

enum class Color::Type
{
	palette2,
	palette16,
	palette256,
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
	white,
	max
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
	white,
	max
};

#endif // !CLEM_COLOR_H_
