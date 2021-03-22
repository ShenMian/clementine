// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_COLOR_H_
#define CLEM_RENDERER_COLOR_H_

#include <stdint.h>

class Color
{
public:
	enum
	{
		black  = 0x00,
		red    = 0x04,
		green  = 0x02,
		yellow = 0x06,
		blue   = 0x01,
		purple = 0x05,
		cyan   = 0x0B,
		aqua   = cyan,
		white  = 0x07
	};

	int8_t fore = 0xF;
	int8_t back = 0x0;

	Color() = default;
	Color(short color); // TODO: short => uint_16
	Color(short fore, short back);
};

#endif // !CLEM_RENDERER_COLOR_H_