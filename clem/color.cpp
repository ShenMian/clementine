// Copyright 2020 SMS
// License(Apache-2.0)
// 字体属性

#include "color.h"
#include <clem/assert.h>

using std::string;

Color::Color()
		: Color(attr::white, attr::black)
{
}

Color::Color(attr f)
		: Color(f, attr::black)
{
}

Color::Color(attr f, attr b)
{
	assert(f < attr::max && b < attr::max, "无效的颜色属性");
	fore = back = nullptr;
}

const std::string& Color::getString() const
{
	assert(fore != nullptr && back != nullptr, "指针无效");
	return string(fore) + string(back);
}
