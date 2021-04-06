// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_TILE_H_
#define CLEM_RENDERER_TILE_H_

#include "Color.h"

/**
 * @brief 瓦片.
 */
class Tile
{
public:
	Tile() = default;
	Tile(wchar_t ch, Color color = Color());

	wchar_t ch = L' ';
	Color   color;

	static const Tile blank;
};

#endif // !CLEM_RENDERER_TILE_H_
