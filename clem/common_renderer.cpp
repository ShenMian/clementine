// Copyright 2020 SMS
// License(Apache-2.0)
// 通用渲染器

#include "common_renderer.h"
#include "terminal.h"

using std::string;

CommonRenderer::CommonRenderer(const Size& size)
		: buffer(size)
{
}

void CommonRenderer::render(const Rect& rect) const
{
	/*
	string line(rect.width, '.');
	for(ushort i = 0; i < rect.height; i++)
	{
		Terminal::Cursor::moveTo(Vector(rect.x, rect.y + i));
		printf("%s", line.c_str());
	}
	*/

	// 绘制
	for(float y = rect.bottom(); y < rect.y; y++)
	{
		Terminal::Cursor::moveTo({rect.x, y});
		for(float x = 0; x < rect.width; x++)
			buffer[{x, y}].put();
	}

	Terminal::Cursor::moveTo({0, 0});
	putchar('\n'); // 刷新缓冲区
}

void CommonRenderer::draw(const Texture& texture, const Point& pos)
{
	buffer.draw(texture, pos);
}

void CommonRenderer::clear()
{
	buffer.clear();
}
