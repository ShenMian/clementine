// Copyright 2020 SMS
// License(Apache-2.0)
// 控制台字体属性

#ifndef CLEM_ATTRIBUTE_H_
#define CLEM_ATTRIBUTE_H_

typedef unsigned short ushort;

#include <string>
#include "os.h"

class Attribute
{
public:
	Attribute();
	Attribute(ushort attr);

	void puts(const std::string& str) const;
	void puts(const char* str) const;
	void putc(char ch) const;

	void on() const;
	void off() const;

	bool operator==(const Attribute& attr);

private:
	void complie(ushort attr);

#ifdef OS_LINUX
	std::string attribute;
#endif

#ifdef OS_WIN
	ushort attribute;
	ushort defaultAttr;
#endif
};

namespace fore
{
enum
{
	normal = 0x0000,
	black  = 0x0001,
	blue   = 0x0002,
	green  = 0x0003,
	cyan   = 0x0004,
	aqua   = 0x0004,
	red    = 0x0005,
	purple = 0x0006,
	yellow = 0x0007,
	white  = 0x0008
};
}

namespace back
{
enum
{
	normal = 0x0000,
	black  = 0x0010,
	blue   = 0x0020,
	green  = 0x0030,
	cyan   = 0x0040,
	aqua   = 0x0040,
	red    = 0x0050,
	purple = 0x0060,
	yellow = 0x0070,
	white  = 0x0080
};
}


namespace mode
{
enum
{
	bold       = 0x0100,
	underline  = 0x0200,
	underscore = 0x0200,
	reverse    = 0x0300
};
}

#endif // CLEM_ATTRIBUTE_H_
