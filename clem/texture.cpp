// Copyright 2020 SMS
// License(Apache-2.0)
// 材质

#include "texture.h"
#include "type.h"
#include <assert.h>

Texture::Texture()
		: Texture(Size(0, 0))
{
}

Texture::Texture(Size size)
		: Texture(size, Tile())
{
}

Texture::Texture(Size size, const Tile& tile)
		: size_(size)
{
	resize(size);

	for(int i = 0; i < size.area(); i++)
		tiles[i] = tile;
}

void Texture::draw(const Tile& tile, const Point& pos)
{
	tiles[pos.x + (pos.y * pos.x)] = tile;
}

void Texture::draw(const Texture& texture, const Point& pos)
{
	for(ushort i = 0; i < texture.size().y; i++)
		for(ushort j = 0; j < texture.size().x; j++)
			draw(texture[pos], {pos.x + i, pos.y + j});
}

void Texture::drawRect(const Tile& tile, const Rect& rect)
{
	for(float i = 0; i < rect.width; i++)
	{
		draw(tile, {rect.x + i, rect.y});
		draw(tile, {rect.x + i, rect.bottom()});
	}
	for(float i = 0; i < rect.height; i++)
	{
		draw(tile, {rect.x, rect.y + i});
		draw(tile, {rect.right(), rect.y + i});
	}
}

const Size& Texture::size() const
{
	return size_;
}

void Texture::resize(Size size)
{
	size_ = size;
	tiles.resize(size_.area());
}

void Texture::clear()
{
	tiles.clear();
	tiles.resize(size_.area());
}

const Tile& Texture::operator[](const Point& pos) const
{
	assert(pos.x <= size_.x && pos.y <= size_.y);
	return tiles[pos.x + (pos.y * pos.x)];
}
