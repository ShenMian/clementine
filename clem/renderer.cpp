// Copyright 2020 SMS
// License(Apache-2.0)
// 渲染器

#include "renderer.h"

void Renderer::render() const
{
	const auto s = texture.getSize();
	for(float x = 0; x < s.x; x++)
	{
		for(float y = 0; y < s.y; y++)
			texture.at({x, y}).print();
		printf("\n");
	}
}

void Renderer::drawTexture(const Texture& t, const Point& p)
{
	texture.drawTexture(t, p);
}

void Renderer::clear()
{
	texture.clear();
}

void Renderer::setSize(Size s)
{
	texture.setSize(s);
}

Size Renderer::getSize() const
{
	return texture.getSize();
}

