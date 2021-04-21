// Copyright 2021 SMS
// License(Apache-2.0)

#include "Text.h"

namespace clem
{
void Text::setText(std::wstring_view t, Color color)
{
	// const auto& pos  = getPisition();
	const auto& size = getSize();
	int         x = 0, y = 0;
	for(auto c : t)
	{
		if(c == '\n' || y == size.y)
		{
			x = 0;
			y++;
		}
		else if(c == '\r')
			x = 0;
		else
		{
			drawPoint({x, y}, Tile(c, color));
			x++;
		}
	}
}
} // namespace clem