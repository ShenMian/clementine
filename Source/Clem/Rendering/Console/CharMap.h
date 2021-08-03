// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

enum CharMap : wchar_t
{
    light_shade  = 0xB0, // ░
    medium_shade = 0xB1, // ▒
    dark_shade   = 0xB2, // ▓

    box_vertical                = 0xB3, // │
    box_vertical_and_left       = 0xB4, // ┤
    box_vertical_and_right      = 0xC3, // ├
    box_down_and_left           = 0xBF, // ┐
    box_up_and_right            = 0xC0, // └
    box_up_and_left             = 0xD9, // ┘
    box_down_and_right          = 0xDA, // ┌
    box_up_and_horizontal       = 0xC1, // ┴
    box_down_and_horizontal     = 0xC2, // ┬
    box_horizontal              = 0xC4, // ─
    box_vertical_and_horizontal = 0xC5, // ┼

    full_block       = 0xDB, // █
    lower_half_block = 0xDC, // ▄
    left_half_block  = 0xDD, // ▌
    right_half_block = 0xDE, // ▐
    upper_half_block = 0xDF  // ▀
};
