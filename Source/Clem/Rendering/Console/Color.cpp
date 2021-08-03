// Copyright 2021 SMS
// License(Apache-2.0)

#include "Color.h"

Color::Color(uint16_t color)
{
    fore = color & 0x0F;
    back = color & 0xF0;
}

Color::Color(uint8_t f, uint8_t b)
    : fore(f), back(b)
{
}