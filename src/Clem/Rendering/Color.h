// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_COLOR_H_
#define CLEM_RENDERER_COLOR_H_

#include <stdint.h>

/**
 * @brief 字体属性.
 */
class Color
{
public:
	enum : uint8_t
	{
		black  = 0x00,
		red    = 0x04,
		green  = 0x02,
		yellow = 0x06,
		blue   = 0x01,
		purple = 0x05,
		cyan   = 0x0B,
		aqua   = cyan,
		white  = 0x07,
		max
	};

	uint8_t fore = white;
	uint8_t back = black;

	Color() = default;
	Color(uint16_t color);
	Color(uint8_t fore, uint8_t back);
};

#endif // !CLEM_RENDERER_COLOR_H_
