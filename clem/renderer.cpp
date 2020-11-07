// Copyright 2020 SMS
// License(Apache-2.0)
// 渲染器

#include "renderer.h"

void Renderer::render() const
{
	assert(false);
}

void Renderer::drawTexture(const Texture& t, const Point& p)
{
	assert(false);
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

